#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

#include <err.h>
#include <stdlib.h>
#include "matrix.h"

void greyscale(SDL_Surface* image);
void black_and_white(SDL_Surface* image);
SDL_Surface* black_and_white2(SDL_Surface* image, int split);
SDL_Surface* otzu(SDL_Surface* img, int w_min, int w_max, int h_min, int h_max);
Uint8* pixelref(SDL_Surface* surface, unsigned x, unsigned y);
Uint32 get_pixel(SDL_Surface* surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface* surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface* scaleSurface(SDL_Surface* img, int width, int height);

#endif
