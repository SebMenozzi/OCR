#ifndef SDL_FUNCTIONS_H_
#define SDL_FUNCTIONS_H_

#include <err.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void init_sdl(void);
void wait_for_keypressed(void);
SDL_Surface* load_image(char *path);
void display_image(SDL_Surface *image);
void greyscale(SDL_Surface* image);
void black_and_white(SDL_Surface* image);
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

#endif
