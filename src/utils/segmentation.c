#include "segmentation.h"
#include <math.h>

void parcours_vertical(SDL_Surface *image, int startline, int endline);

void remplissage(SDL_Surface *image, int startline, int endline, int startcolum, int endcolum);

//horizontal course of the image
void parcours_horizontal(SDL_Surface *image)
{
  int oneblack = 0 ; // bool to know if we met a black pixel
  int startline = 0; // First line to be met
  int endline; //last line to be met

  for(int y = 0; y < image->h; y++)
  {
    int oneblank = 1;
    for(int x = 0; x < image->w; x++)
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
            x = image->w;
        }
        else
        {
          x = image->w;
        }
      }
    }
    if (oneblack == 1 && oneblank == 1)
    {
      endline = y - 1;
      parcours_vertical(image, startline, endline);
      oneblack = 0;
    }
  }
}

//vertical course of the image
void parcours_vertical(SDL_Surface *image, int startline, int endline)
{
  int oneblack = 0;
  int startcolum = 0; // first colum to be met
  int endcolum; // last line to be met
  for(int x = 0; x < image->w; x++)
  {
    int oneblank = 1;
    for( int y= startline; y<= endline; y++)
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
          y = endline+1;
        }
        else
        {
          y= endline + 1;
        }
      }
    }
    if (oneblack == 1 && oneblank == 1)
    {
      endcolum = x - 1;
      remplissage(image, startline, endline, startcolum, endcolum);
      oneblack = 0;
    }
  }
}

//Change the color of the pixel which are in the square
void remplissage(SDL_Surface *image, int startline, int endline, int startcolum, int endcolum)
{

  Uint8 r = 255, g = 0, b = 0;
  Uint32 pixel = SDL_MapRGB(image->format, r, g, b);

  for (int y = startline; y <= endline; y++)
  {
    // left border
    put_pixel(image, startcolum - 1, y, pixel);

    // righ border
    put_pixel(image, endcolum + 1, y, pixel);
  }

  for (int x = startcolum; x <= endcolum; x++)
  {
    // top border
    put_pixel(image, x, startline, pixel);

    // bottom border
    put_pixel(image, x, endline + 1, pixel);
  }

  // Create the image

  SDL_Surface *imageNotResized;
  SDL_Surface *imageIn28x28;

  size_t height = endline - startline,
         width = endcolum - startcolum + 1;

  imageNotResized = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  imageIn28x28 = SDL_CreateRGBSurface(0, 28, 28, 32, 0, 0, 0, 0);

  for (size_t y = 0; y < height; y++)
  {
    for (size_t x = 0; x < width; x++)
    {
      Uint32 pixel = get_pixel(image, startcolum + x, startline + y + 1);

      put_pixel(imageNotResized, x, y, pixel);
    }
  }

  // Resize the image
  SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 28;
	rect.h = 28;
  SDL_BlitScaled(imageNotResized, NULL, imageIn28x28, &rect);

  // free old not resized image
  SDL_FreeSurface(imageNotResized);

  // Save the image
  char *buffer = malloc(20 * sizeof(char));

  sprintf(buffer, "./data/test/%d_%d.bmp", startline, startcolum);

  SDL_SaveBMP(imageIn28x28, buffer);

  // free buffer and the resized 28x28 image
  free(buffer);
  SDL_FreeSurface(imageIn28x28);
}
