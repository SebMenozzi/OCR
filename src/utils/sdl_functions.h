#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_

#include <err.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void init_sdl(void);
void quit_sdl(void);
SDL_Surface* load_image(char* path);

#endif
