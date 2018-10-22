#include "segmentation.h"

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
  for (int y = startline; y <= endline; y++)
  {
    for (int x = startcolum; x <= endcolum; x++)
    {
      Uint32 pixel = get_pixel(image, x, y);
      Uint8 r = 255, g = 0, b = 0;
      pixel = SDL_MapRGB(image->format, r, g, b);
      put_pixel(image, x, y, pixel);
    }
  }
}
