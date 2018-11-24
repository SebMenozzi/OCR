#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

typedef struct {
  // topology
  size_t nb_input;
  size_t nb_hidden;
  size_t nb_output;
  // layers
  Matrix* input_layer;
  Matrix* hidden_layer;
  Matrix* output_layer;
  //weights
  Matrix* input_hidden_weights;
  Matrix* hidden_output_weights;
  // bias
  Matrix* input_hidden_bias;
  Matrix* hidden_output_bias;
  // target
  Matrix* target;
  // deltas to update weights and biases
  Matrix* delta_hidden;
  Matrix* delta_output;
  //Matrix* delta_input_weights;
  //Matrix* delta_hidden_weights;
  // error rate
  double mae_rate;
  double rmse_rate;
  // parameters
  double learning_rate;
  //double momentum;
} NeuralNetwork;

NeuralNetwork new_network(size_t nb_input, size_t nb_hidden, size_t nb_output, double learning_rate/*, double momentum*/);
void randomize_weights_bias(NeuralNetwork net);
void forward_propagate(NeuralNetwork net, double* inputs);
void back_propagate(NeuralNetwork net, double* target);
void print_error_rate(NeuralNetwork net);
void calculate_deltas(NeuralNetwork net);
void update_weights(NeuralNetwork net);
void update_bias(NeuralNetwork net);
void save_network(NeuralNetwork net, char* directory);
void load_network(NeuralNetwork net, char* directory);
void free_network(NeuralNetwork net);
Matrix* get_network_result(NeuralNetwork net, double* inputs);

#endif
