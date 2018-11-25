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
