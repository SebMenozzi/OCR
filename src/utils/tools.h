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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char* create_path(char* directory, char* name);
double random_value();
float sigmoid(float x);
float sigmoid_prime(float x);
double get_value_pixel(SDL_Surface* img, size_t x, size_t y);
int create_folder(char* path);
int folder_exists(char* path);
char* get_file_name(char* path);
void rmtree(const char path[]);
void add(char **s, char c);
void add_character(const char *filepath, const char character);
int load_file(const char *filename, char **result);

#endif
