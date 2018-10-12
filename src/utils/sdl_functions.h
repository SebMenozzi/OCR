#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>

void init_sdl(void);
void wait_for_keypressed(void);
SDL_Surface* load_image(char *path);

#endif
