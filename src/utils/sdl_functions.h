#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void init_sdl(void);
void wait_for_keypressed(void);
SDL_Surface* load_image(char *path);
void greyscale(SDL_Surface* image);
void black_and_white(SDL_Surface* image);
Uint32 get_pixel(SDL_Surface *surface, int x, int y);
void put_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif
