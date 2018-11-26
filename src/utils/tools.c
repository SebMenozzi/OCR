#include "tools.h"

char* create_path(char* directory, char* name)
{
  char* fullpath;
  fullpath = malloc(strlen(directory) + strlen("/") + strlen(name) + 1);
  strcpy(fullpath, directory); // copy directory in fullpath
  strcat(fullpath, "/"); // add "/"
  strcat(fullpath, name); // add the name
  return fullpath;
}

double random_value() // between -1 and 1
{
  return 2.0f * rand() / RAND_MAX - 1;
}

float sigmoid(float x) // sigmoid function
{
  return 1.0 / (1.0 + exp(-x));
}

float sigmoid_prime(float x) // derivative of sigmoid function
{
  return x * (1.0 - x);
}

int create_folder(char* path)
{
  int error = 0;
  #if defined(_WIN32)
    error = _mkdir(path);
  #else
    error= mkdir(path, 0733);
  #endif
  return error;
}

int folder_exists(char* path)
{
  struct stat st;
  return stat(path, &st);
}
