#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

typedef struct {
  size_t nb_input;
  size_t nb_hidden;
  size_t nb_output;
  Matrix* input_layer;
  Matrix* hidden_layer;
  Matrix* output_layer;
  Matrix* input_weights;
  Matrix* hidden_weights;
  Matrix* input_bias;
  Matrix* hidden_bias;
  Matrix* target;
  //Matrix* delta_input_weights;
  //Matrix* delta_hidden_weights;
  Matrix* delta_hidden;
  Matrix* delta_output;
  double mae_rate;
  double rmse_rate;
  double learning_rate;
  //double momentum;
} NeuralNetwork;

NeuralNetwork new_network(size_t nb_input, size_t nb_hidden, size_t nb_output, double learning_rate/*, double momentum*/);
void randomize_weights_bias(NeuralNetwork network);
void forward_propagate(NeuralNetwork network, double* inputs);
void back_propagate(NeuralNetwork net, double* target);
void print_error_rate(NeuralNetwork net);
void calculate_deltas(NeuralNetwork net);
void update_weights(NeuralNetwork net);
void update_bias(NeuralNetwork net);
void free_network(NeuralNetwork network);

#endif
