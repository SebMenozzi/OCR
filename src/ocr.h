#ifndef OCR_H
#define OCR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "utils/sdl_functions.h"
#include "utils/image_operations.h"
#include "utils/segmentation.h"
#include "utils/matrix.h"
#include "utils/neural_network.h"
#include "utils/tools.h"

void OCR(char* file);

#endif
