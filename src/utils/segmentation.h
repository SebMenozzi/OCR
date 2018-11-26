#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "image_operations.h"
#include "matrix.h"
#include "tools.h"

void horizontal_course(SDL_Surface* image);
void vertical_course(SDL_Surface* image, int startline, int endline);
void surround(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum);
void extract_characters(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum);

#endif
