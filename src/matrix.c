#include <stdio.h>
#include "matrix.h"

Matrix* new_matrix(size_t rows, size_t cols)
{
  Matrix* mat = malloc(sizeof(Matrix));
  mat->rows = rows;
  mat->cols = cols;
  mat->values = calloc(rows * cols, sizeof(double));
  return mat;
}

Matrix* copy_matrix(Matrix* mat)
{
  Matrix* mat2 = new_matrix(mat->rows, mat->cols);

  // for each row
  for (size_t r = 0; r < mat->rows; r++)
  {
    // for each column
    for (size_t c = 0; c < mat->cols; c++)
    {
      mat2->values[r * mat2->rows + c] = mat->values[r * mat->rows + c];
    }
  }

  return mat2;
}

Matrix* transpose_matrix(Matrix* mat)
{
  Matrix* transpose = new_matrix(mat->cols, mat->rows);

  // for each row
  for (size_t r = 0; r < mat->rows; r++)
  {
    // for each column
    for (size_t c = 0; c < mat->cols; c++)
    {
      transpose->values[c * mat->rows + r] = mat->values[r * mat->cols + c];
    }
  }

  return transpose;
}

Matrix* add_scalar(Matrix* mat, double scalar)
{
  Matrix* result = new_matrix(mat->rows, mat->cols);

  // for each row
  for (size_t r = 0; r < mat->rows; r++)
  {
    // for each column
    for (size_t c = 0; c < mat->cols; c++)
    {
      result->values[r * mat->cols + c] = mat->values[r * mat->cols + c] + scalar;
    }
  }

  return result;
}

Matrix* multiply_scalar(Matrix* mat, double scalar)
{
  Matrix* result = new_matrix(mat->rows, mat->cols);

  // for each row
  for (size_t r = 0; r < mat->rows; r++)
  {
    // for each column
    for (size_t c = 0; c < mat->cols; c++)
    {
      result->values[r * mat->cols + c] = mat->values[r * mat->cols + c] * scalar;
    }
  }

  return result;
}

Matrix* add_matrices(Matrix* mat1, Matrix* mat2)
{
  Matrix* result = new_matrix(mat1->rows, mat1->cols);

  // for each row
  for (size_t r = 0; r < mat1->rows; r++)
  {
    // for each column
    for (size_t c = 0; c < mat1->cols; c++)
    {
      double value1 = mat1->values[r * mat1->cols + c];
      double value2 = mat2->values[r * mat2->cols + c];

      result->values[r * mat1->cols + c] = value1 + value2;
    }
  }

  return result;
}

Matrix* multiply_matrices(Matrix* mat1, Matrix* mat2)
{
  Matrix* result = new_matrix(mat1->rows, mat2->cols);

  // for each row
  for (size_t r = 0; r < mat1->rows; r++)
  {
    // for each column
    for (size_t c = 0; c < mat2->cols; c++)
    {
      double sum = 0.0;

      for (size_t i = 0; i < mat1->cols; i++)
      {
        double value1 = mat1->values[c * mat1->cols + i];
        double value2 = mat2->values[i * mat2->cols + r];
        sum += value1 * value2;
      }

      result->values[c * mat2->cols + r] = sum;
    }
  }

  return result;
}

void print_matrix(Matrix* mat)
{
  // for each row
  for (size_t r = 0; r < mat->rows; r++)
  {
    // for each column
    for (size_t c = 0; c < mat->cols; c++)
    {
      printf("%.2f ", mat->values[r * mat->cols + c]);

      // last value in a column with after a line break
      if (c == mat->cols - 1) {
        printf("\n");
      }
    }
  }
  printf("\n");
}

void save_matrix(Matrix* mat, char* name)
{
  FILE* file = fopen(name, "w");
  for(size_t r = 0; r < mat->rows; ++r)
  {
    for(size_t c = 0; c < mat->cols; ++c)
    {
      fprintf(file, "%f\n", mat->values[r * mat->cols + c]);
    }
  }
  fclose(file);
}

void load_matrix(Matrix* mat, char* name)
{
  int sizeMax = 15;
  char *line = calloc(15, sizeof(char));

  FILE* file = fopen(name, "r");
  for(size_t r = 0; r < mat->rows; ++r)
  {
    for(size_t c = 0; c < mat->cols; ++c)
    {
      fgets(line, sizeMax, file);
      strtok(line, "\n");
      mat->values[r * mat->cols + c] = atof(line);
    }
  }
  fclose(file);
}

void free_matrix(Matrix* mat)
{
  free(mat->values);
  free(mat);
}

/*
  -----------------
  Expected result :
  -----------------

  m1 =
     1   2
  m2 =
     1   2
     3   4
  m3 =
     1   2
     3   4
     5   6
  m4 =
     1   0   3
     1   2   0
     0   2   3
     1   0   3
  m5 =
     1   2   3   4
     5   6   7   8
     9  10  11  12
  m1_tr =
     1
     2
  m2_tr =
     1   3
     2   4
  m3_tr =
     1   3   5
     2   4   6
  m4_tr =
     1   1   0   1
     0   2   2   0
     3   0   3   3
  m5_tr =
     1   5   9
     2   6  10
     3   7  11
     4   8  12
  m3_plus_m3 =
     2   4
     6   8
    10  12
  m4_plus_m5tr =
     2   5  12
     3   8  10
     3   9  14
     5   8  15
  m5_plus_m4tr =
     2   3   3   5
     5   8   9   8
    12  10  14  15
  m2_times_m2 =
     7  10
    15  22
  m4_times_m5 =
    28  32  36  40
    11  14  17  20
    37  42  47  52
    28  32  36  40
  m5_times_m4 =
     7  10  24
    19  26  60
    31  42  96
*/

void test_matrix()
{
  Matrix* m1 = new_matrix(1, 2);
  double v1[] = {
    1, 2
  };
  m1->values = v1;

  Matrix* m2 = new_matrix(2, 2);
  double v2[] = {
    1, 2,
    3, 4
  };
  m2->values = v2;

  Matrix* m3 = new_matrix(3, 2);
  double v3[] = {
    1, 2,
    3, 4,
    5, 6
  };
  m3->values = v3;

  Matrix* m4 = new_matrix(4, 3);
  double v4[] = {
    1, 0, 3,
    1, 2, 0,
    0, 2, 3,
    1, 0, 3
  };
  m4->values = v4;

  Matrix* m5 = new_matrix(3, 4);
  double v5[] = {
    1, 2,  3,  4,
    5, 6,  7,  8,
    9, 10, 11, 12,
  };
  m5->values = v5;

  Matrix* m1_tr = transpose_matrix(m1);
  Matrix* m2_tr = transpose_matrix(m2);
  Matrix* m3_tr = transpose_matrix(m3);
  Matrix* m4_tr = transpose_matrix(m4);
  Matrix* m5_tr = transpose_matrix(m5);

  Matrix* m3_plus_m3 = add_matrices(m3, m3);
  Matrix* m4_plus_m5tr = add_matrices(m4, m5_tr);
  Matrix* m5_plus_m4tr = add_matrices(m5, m4_tr);

  Matrix* m2_times_m2 = multiply_matrices(m2, m2);
  Matrix* m4_times_m5 = multiply_matrices(m4, m5);
  Matrix* m5_times_m4 = multiply_matrices(m5, m4);

  print_matrix(m1);
  print_matrix(m2);
  print_matrix(m3);
  print_matrix(m4);
  print_matrix(m5);

  print_matrix(m1_tr);
  print_matrix(m2_tr);
  print_matrix(m3_tr);
  print_matrix(m4_tr);
  print_matrix(m5_tr);

  print_matrix(m3_plus_m3);
  print_matrix(m4_plus_m5tr);
  print_matrix(m5_plus_m4tr);

  print_matrix(m2_times_m2);
  print_matrix(m4_times_m5);
  print_matrix(m5_times_m4);

  // free matrices from memory

  free_matrix(m1);
  free_matrix(m2);
  free_matrix(m3);
  free_matrix(m4);
  free_matrix(m5);

  free_matrix(m1_tr);
  free_matrix(m2_tr);
  free_matrix(m3_tr);
  free_matrix(m4_tr);
  free_matrix(m5_tr);

  free_matrix(m3_plus_m3);
  free_matrix(m4_plus_m5tr);
  free_matrix(m5_plus_m4tr);

  free_matrix(m2_times_m2);
  free_matrix(m4_times_m5);
  free_matrix(m5_times_m4);
}
