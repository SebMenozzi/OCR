#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "image_operations.h"
#include "matrix.h"
#include "tools.h"

void horizontal_course(SDL_Surface* image,
                       void (*fun)(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum, size_t counter)
                      );
int vertical_course(SDL_Surface* image,
                    size_t offset,
                    int startline,
                    int endline,
                    void (*fun)(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum, size_t counter)
                   );

#endif
