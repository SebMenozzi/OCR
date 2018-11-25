#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* create_path(char* directory, char* name);
double random_value();
float sigmoid(float x);
float sigmoid_prime(float x);

#endif
