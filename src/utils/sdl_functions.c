#include "sdl_functions.h"

void init_sdl(void) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Could not initialize SDL: %s.\n", SDL_GetError());
  }
}

void wait_for_keypressed(void) {
  int isRunning = 1;
  SDL_Event event;

  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
          isRunning = 0;
          break;
      }
    }

    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            isRunning = 0;
            break;
        }
    }
  }
}

SDL_Surface* load_image(char* path) {
  SDL_Surface* image;
  image = IMG_Load(path);
  if (!image) {
    printf("Can't load %s : %s\n", path, IMG_GetError());
  }
  return image;
}

Uint32 get_pixel(SDL_Surface *surface, int x, int y)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[ (y * surface->w ) + x];
}

void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint32 *pixels = (Uint32 *)surface->pixels;
    pixels[( y * surface->w ) + x] = pixel;
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

void blacknwhite(SDL_Surface *image)
{
  for(int y = 0; y < image->h; y++) {
    for(int x = 0; x < image->w; x++) {
      Uint32 pixel = get_pixel(image, x, y);
      Uint8 r = 0, g = 0, b = 0;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      if(r >= 127 && g >= 127 && b >= 127) {
        r = 255;
        g = 255;
        b = 255;
      }
      else {
        r = 0;
        g = 0;
        b = 0;
      }
      pixel = SDL_MapRGB(image->format, r, g, b);
      put_pixel(image, x, y, pixel);
    }
  }
}
