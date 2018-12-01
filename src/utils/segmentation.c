#include "segmentation.h"
#include "../config.h"

// Horizontal course of the image
void horizontal_course(SDL_Surface* image,
                       void (*fun)(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum, size_t counter)
                      )
{
  size_t counter = 1;

  int oneblack = 0 ; // Boolean to know if we met a black pixel
  int startline = 0; // First line to be met
  int endline; // Last line to be met

  for(int y = 0; y < image->h; ++y)
  {
    int oneblank = 1;
    for(int x = 0; x < image->w; ++x)
    {
      Uint32 pixel = get_pixel(image, x, y);
      Uint8 r = 0, g = 0, b = 0;

      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      if (r == 0)
      {
        oneblank = 0;
        if (oneblack == 0)
        {
          oneblack = 1;
          startline = y;
        }
        x = image->w;
      }
    }
    if (oneblack == 1 && oneblank == 1)
    {
      endline = y - 1;
      counter = vertical_course(image, counter, startline, endline, fun);
      oneblack = 0;
    }
  }
}

// vertical course of the image
int vertical_course(SDL_Surface* image,
                    size_t counter,
                    int startline,
                    int endline,
                    void (*fun)(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum, size_t counter))
{
  int oneblack = 0;
  int startcolum = 0; // first colum to be met
  int endcolum; // last line to be met

  for(int x = 0; x < image->w; ++x)
  {
    int oneblank = 1;
    for(int y = startline; y <= endline; ++y)
    {
      Uint32 pixel = get_pixel(image, x, y);
      Uint8 r = 0, g = 0, b = 0;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      if (r == 0)
      {
        oneblank = 0;
        if (oneblack == 0)
        {
          oneblack = 1;
          startcolum = x;
        }
        y = endline + 1;
      }
    }

    if (oneblack == 1 && oneblank == 1)
    {
      endcolum = x - 1;

      // function that will be called for each character
      fun(image, startline, endline, startcolum, endcolum, counter);

      counter += 1;

      oneblack = 0;
    }
  }

  return counter;
}
/*
void surround(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum, size_t offset)
{
  Uint8 r = 255, g = 0, b = 0;
  Uint32 pixel = SDL_MapRGB(image->format, r, g, b);

  for (int y = startline; y <= endline; ++y)
  {
    // left border
    put_pixel(image, startcolum - 1, y, pixel);

    // righ border
    put_pixel(image, endcolum + 1, y, pixel);
  }

  for (int x = startcolum; x <= endcolum; ++x)
  {
    // top border
    put_pixel(image, x, startline, pixel);

    // bottom border
    put_pixel(image, x, endline + 1, pixel);
  }
}
*/
