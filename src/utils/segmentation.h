#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL/sdl_functions.h"

void parcours_horizontal(SDL_Surface *image);
void parcours_vertical(SDL_Surface *image, int startline, int endline);
void remplissage(SDL_Surface *image, int startline, int endline, int startcolum, int endcolum);

#endif
