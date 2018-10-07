#include "mnist.h"
#include <SDL2/SDL.h>

const int WIDTH  = 640;
const int HEIGHT = 480;

void OCR()
{
   /*
    int CURSOR = 0;
    load_mnist();

    for (size_t i = 0; i < 784; i++) {
        printf("%1.1f ", train_image[CURSOR][i]);
        if ((i+1) % 28 == 0) putchar('\n');
    }

    //printf("label: %c\n", 96 + train_label[CURSOR]);
    printf("label: %d\n", train_label[CURSOR]);
    */

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
    }
    else
    {
      SDL_Window* window = 0;
      window = SDL_CreateWindow
      (
          "MMGD OCR", SDL_WINDOWPOS_UNDEFINED,
          SDL_WINDOWPOS_UNDEFINED,
          WIDTH,
          HEIGHT,
          SDL_WINDOW_SHOWN
      );

      SDL_Renderer* renderer = 0;
      renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

      SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
      SDL_RenderClear(renderer);
      SDL_RenderPresent(renderer);

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

      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
    }
}
