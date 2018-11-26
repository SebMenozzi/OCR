#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "image_operations.h"
#include <sys/types.h>  // For stat()
#include <sys/stat.h>   // For stat()

char* create_path(char* directory, char* name);
double random_value();
float sigmoid(float x);
float sigmoid_prime(float x);
double get_value_pixel(SDL_Surface* img, size_t x, size_t y);
int create_folder(char* path);
int folder_exists(char* path);

#endif
