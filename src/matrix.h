#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _Matrix {
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
void print_matrix(Matrix* mat);
void free_matrix(Matrix* mat);
void test_matrix();

#endif
