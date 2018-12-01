#ifndef IMAGE_OPERATIONS_H
#define IMAGE_OPERATIONS_H

#include <err.h>
#include <stdlib.h>
#include "matrix.h"

void greyscale(SDL_Surface* image);
void black_and_white(SDL_Surface* image);
Uint8* pixelref(SDL_Surface* surface, unsigned x, unsigned y);
Uint32 get_pixel(SDL_Surface* surface, unsigned x, unsigned y);
void put_pixel(SDL_Surface* surface, unsigned x, unsigned y, Uint32 pixel);

#endif
