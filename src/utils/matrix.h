#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tools.h"

typedef struct {
  size_t rows;
  size_t cols;
  double* values;
} Matrix;

Matrix* new_matrix(size_t rows, size_t cols);
Matrix* copy_matrix(Matrix* mat);
Matrix* transpose_matrix(Matrix* mat);
Matrix* add_scalar(Matrix* mat, double scalar);
Matrix* multiply_scalar(Matrix* mat, double scalar);
Matrix* add_matrices(Matrix* mat1, Matrix* mat2);
Matrix* multiply_matrices(Matrix* mat1, Matrix* mat2);
Matrix* img_to_matrix(SDL_Surface* img); // should not be here...
Matrix* resize_matrix(Matrix* mat, size_t width, size_t height);
void print_matrix(Matrix* mat);
void save_matrix(Matrix* mat, char* directory, char* name);
void load_matrix(Matrix* mat, char* directory, char* name);
void free_matrix(Matrix* mat);
void test_matrix();

#endif
