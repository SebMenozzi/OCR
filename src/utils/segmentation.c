#include "segmentation.h"

// Horizontal course of the image
void horizontal_course(SDL_Surface* image)
{
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
      vertical_course(image, startline, endline);
      oneblack = 0;
    }
  }
}

// vertical course of the image
void vertical_course(SDL_Surface* image, int startline, int endline)
{
  int oneblack = 0;
  int startcolum = 0; // first colum to be met
  int endcolum; // last line to be met
  for(int x = 0; x < image->w; ++x)
  {
    int oneblank = 1;
    for( int y = startline; y <= endline; ++y)
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
      surround(image, startline, endline, startcolum, endcolum);
      extract_characters(image, startline, endline, startcolum, endcolum);
      oneblack = 0;
    }
  }
}

void surround(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum)
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


void extract_characters(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum)
{
  size_t height = endline - startline,
         width = endcolum - startcolum + 1;

  Matrix* mat = new_matrix(height, width);

  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      mat->values[y * width + x] = get_value_pixel(image, startcolum + x, startline + y + 1);
    }
  }

  char* name = malloc(10 * sizeof(char));
  sprintf(name, "%d_%d.m", startline, startcolum);

  Matrix* mat_28x28 = resize_matrix(mat, 28, 28);

  //print_matrix(matrix_28x28);
  
  save_matrix(mat_28x28, "data/raw_characters", name);

  free_matrix(mat_28x28);
  free_matrix(mat);
}
