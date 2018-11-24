#include "ocr.h"

const int WIDTH  = 1300;
const int HEIGHT = 900;

void OCR(char* file)
{
  SDL_Init(SDL_INIT_EVERYTHING);
  IMG_Init(IMG_INIT_PNG);

  int quit = 0;
  SDL_Event event;

  SDL_Window* window = SDL_CreateWindow("MMGD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
  SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);

  SDL_Surface* image = load_image(file);
  greyscale(image);
  black_and_white(image);
  //image = black_and_white2(image, 1);
  parcours_horizontal(image);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(render, image);

  while(!quit)
  {
    SDL_Rect dstrect = { 0, 0, image->w, image->h};

    SDL_PollEvent(&event);
    switch (event.type)
    {
      case SDL_QUIT:
        quit = 1;
        break;

      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          quit = 1;
        }
        break;
    }

    SDL_RenderClear(render);
    SDL_RenderCopy(render, texture, NULL, &dstrect);
    SDL_RenderPresent(render);
  }

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image);
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();

  /*
  SDL_Surface* image_surface;

  IMG_Init(IMG_INIT_PNG);

  init_sdl();

  image_surface = load_image(file);
  greyscale(image_surface);
  black_and_white(image_surface);
  parcours_horizontal(image_surface);

  display_image(image_surface);
  */
}
