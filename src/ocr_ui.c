#include "ocr_ui.h"
#include "config.h"

const int WIDTH  = 1300;
const int HEIGHT = 900;

void OCR_UI(char* file)
{
  printf("%s\n", file);
  /*
  init_sdl();

  int quit = 0;
  SDL_Event event;

  SDL_Window* window = SDL_CreateWindow("MMGD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_Surface* image = load_image(file);
  greyscale(image);
  black_and_white(image);
  horizontal_course(image, RAW_CHARACTERS_PATH, 0);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);

  while(!quit)
  {
    SDL_Rect rect = { 0, 0, image->w, image->h};

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

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(image);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  quit_sdl();
  */
}
