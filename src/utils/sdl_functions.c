#include "sdl_functions.h"

void SDL_FreeSurface(SDL_Surface *surface);

void init_sdl()
{
  // Init only the video part.
  // If it fails, die with an error message.
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());

   IMG_Init(IMG_INIT_PNG);
}

void quit_sdl()
{
  IMG_Quit();
  SDL_Quit();
}

SDL_Surface* load_image(char* path)
{
  SDL_Surface *img;

  // Load an image using SDL_image with format detection.
  // If it fails, die with an error message.
  img = IMG_Load(path);
  if (!img)
      errx(3, "can't load %s: %s", path, IMG_GetError());

  return img;
}
