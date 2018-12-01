#include "image_operations.h"

Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y) {
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
    case 1:
      return *p;
    case 2:
      return *(Uint16 *)p;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
    case 4:
      return *(Uint32 *)p;
  }
  return 0;
}

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
    case 1:
      *p = pixel;
      break;
    case 2:
      *(Uint16 *)p = pixel;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        p[0] = (pixel >> 16) & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
      } else {
        p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
      }
      break;
    case 4:
      *(Uint32 *)p = pixel;
      break;
  }
}

void greyscale(SDL_Surface *image)
{
  for(int y = 0; y < image->h; y++) {
    for(int x = 0; x < image->w; x++) {
      Uint32 pixel = get_pixel(image, x, y);
      Uint8 r = 0, g = 0, b = 0;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      Uint8 sum = r * 0.3 + g * 0.59 + b * 0.11;
      pixel = SDL_MapRGB(image->format, sum, sum, sum);
      put_pixel(image, x, y, pixel);
    }
  }
}

void black_and_white(SDL_Surface *image)
{
  for(int y = 0; y < image->h; y++) {
    for(int x = 0; x < image->w; x++) {
      Uint32 pixel = get_pixel(image, x, y);
      Uint8 r = 0, g = 0, b = 0;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      r = (r >= 127) ? 255 : 0;
      g = (g >= 127) ? 255 : 0;
      b = (b >= 127) ? 255 : 0;
      pixel = SDL_MapRGB(image->format, r, g, b);
      put_pixel(image, x, y, pixel);
    }
  }
}

double get_value_pixel(SDL_Surface* img, size_t x, size_t y)
{
  Uint32 pixel = get_pixel(img, x, y);

  Uint8 r = 0, g = 0, b = 0;
  SDL_GetRGB(pixel, img->format, &r, &g, &b);

  return (double) 1.0 - (r / 255);
}
