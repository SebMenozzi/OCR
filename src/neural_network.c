#include "neural_network.h"

NeuralNetwork new_network(size_t nb_input, size_t nb_hidden, size_t nb_output, double learning_rate, double momentum)
{
  NeuralNetwork net;
  net.nb_input = nb_input;
  net.nb_hidden = nb_hidden;
  net.nb_output = nb_output;

  net.input_layer = new_matrix(nb_input, 1);
  net.hidden_layer = new_matrix(nb_hidden, 1);
  net.output_layer = new_matrix(nb_output, 1);

  net.input_weights = new_matrix(nb_input, nb_hidden);
  net.delta_input_weights = new_matrix(nb_input, nb_hidden);
  net.input_bias = new_matrix(nb_hidden, 1);

  net.hidden_weights = new_matrix(nb_hidden, nb_output);
  net.delta_hidden_weights = new_matrix(nb_hidden, nb_output);
  net.hidden_bias = new_matrix(nb_output, 1);

  net.target = new_matrix(nb_output, 1);

  net.output_cost_error = new_matrix(nb_output, 1);
  net.hidden_cost_error = new_matrix(nb_output, 1);

  net.mae_rate = 0;
  net.rmse_rate = 0;

  net.learning_rate = learning_rate;
  net.momentum = momentum;

  // put random weights and bias in the net
  randomize_weights_bias(net);

  return net;
}

double random_value() { // between -1 and 1
  return 2.0f * rand() / RAND_MAX - 1;
}

void randomize_weights_bias(NeuralNetwork net)
{
  // initalize input weights and bias
  for (size_t c = 0; c < net.nb_hidden; ++c)
  {
    for (size_t r = 0; r < net.nb_input; ++r)
    {
      net.input_weights->values[r * net.nb_hidden + c] = random_value();
    }
    net.input_bias->values[c] = random_value();
  }

  // initalize hidden weights and bias
  for (size_t c = 0; c < net.nb_output; ++c)
  {
    for (size_t r = 0; r < net.nb_hidden; ++r)
    {
      net.hidden_weights->values[r * net.nb_output + c] = random_value();
    }
    net.hidden_bias->values[c] = random_value();
  }
}

// activation function
float sigmoid(float x)
{
  return 1.0 / (1.0 + exp(-x));
}

// derivative of activation function
float sigmoid_prime(float x)
{
  return x * (1.0 - x);
}

void forward_propagate(NeuralNetwork net, double* inputs)
{
  // initalize the input layer
  net.input_layer->values = inputs;

  double sum, weight, layer, bias;

  // Update hidden layer
  for (size_t c = 0; c < net.nb_hidden; ++c)
  {
    sum = 0.0;
    for (size_t r = 0; r < net.nb_input; ++r)
    {
      weight = net.input_weights->values[r * net.nb_hidden + c];
      layer = net.input_layer->values[r];

      sum += weight * layer;
    }
    bias = net.input_bias->values[c];
    net.hidden_layer->values[c] = sigmoid(sum + bias);
  }

  // Update output layer
  for (size_t c = 0; c < net.nb_output; ++c)
  {
    sum = 0.0;
    for (size_t r = 0; r < net.nb_hidden; ++r)
    {
      weight = net.hidden_weights->values[r * net.nb_output + c];
      layer = net.hidden_layer->values[r];

      sum += weight * layer;
    }
    bias = net.hidden_bias->values[c];
    net.output_layer->values[c] = sigmoid(sum + bias);
  }
}

void back_propagate(NeuralNetwork net, double* target)
{
  // we put the target
  net.target->values = target;

  print_error_rate(net); // for debugging
  calculate_cost_function(net);
  update_weights(net);
  //update_bias(net);
}

void print_error_rate(NeuralNetwork net)
{
  double output, target, mae_rate = 0, rmse_rate = 0;

  // Calculate the overall net error (MAE AND RMSE Methods)
  // https://medium.com/human-in-a-machine-world/mae-and-rmse-which-metric-is-better-e60ac3bde13d
  for (size_t r = 0; r < net.nb_output; ++r)
  {
    output = net.output_layer->values[r];
    target = net.target->values[r];

    mae_rate += fabs(target - output);
    rmse_rate += pow(target - output, 2);
  }
  mae_rate /= net.nb_output;
  rmse_rate /= net.nb_output;
  rmse_rate = sqrt(rmse_rate);

  net.mae_rate = mae_rate;
  net.rmse_rate = rmse_rate;

  printf("MAE RATE: %.2f / RMSE RATE: %.2f\n", net.mae_rate, net.rmse_rate);
}

void calculate_cost_function(NeuralNetwork net)
{
  // Calulate cost function for output neurons
  double output, derivate, target, error;
  for (size_t r = 0; r < net.nb_output; ++r)
  {
    output = net.output_layer->values[r];
    derivate = sigmoid_prime(output);
    target = net.target->values[r];
    error = (target - output) * derivate;
    net.output_cost_error->values[r] = error;
  }

  // Calculate cost function for hidden neurons
  double sum, weight, delta;
  for (size_t r = 0; r < net.nb_hidden; ++r)
  {
    sum = 0.0;
    for (size_t c = 0; c < net.nb_output; ++c)
    {
      weight = net.hidden_weights->values[r * net.nb_output + c];
      delta = net.output_cost_error->values[c];
      sum += weight * delta;
    }
    output = net.hidden_layer->values[r];
    derivate = sigmoid_prime(output);
    net.hidden_cost_error->values[r] = sum * derivate;
  }
}

void update_weights(NeuralNetwork net)
{
  double gradient, dweight, error, layer;

  // Weights between input and hidden layers
  for (size_t c = 0; c < net.nb_hidden; ++c)
  {
    for(size_t r = 0; r < net.nb_input; ++r)
    {
      error = net.hidden_cost_error->values[c];
      layer = net.input_layer->values[r];
      dweight = net.delta_input_weights->values[r * net.nb_hidden + c];
      gradient = error * layer;
      net.input_weights->values[r * net.nb_hidden + c] += gradient * net.learning_rate +
                                                          dweight * net.momentum;
      net.delta_input_weights->values[r * net.nb_hidden + c] = gradient * net.learning_rate;
    }
  }

  // Weights between hidden and output layers
  for (size_t c = 0; c < net.nb_output; ++c)
  {
    for(size_t r = 0; r < net.nb_hidden; ++r)
    {
      error = net.output_cost_error->values[c];
      layer = net.hidden_layer->values[r];
      dweight = net.delta_hidden_weights->values[r * net.nb_output + c];
      gradient = error * layer;
      net.hidden_weights->values[r * net.nb_output + c] += gradient * net.learning_rate +
                                                           dweight * net.momentum;
      net.delta_hidden_weights->values[r * net.nb_output + c] = gradient * net.learning_rate;
    }
  }
}
/*
void update_bias(NeuralNetwork net)
{

}
*/
void free_network(NeuralNetwork net)
{
  free_matrix(net.input_layer);
  free_matrix(net.hidden_layer);
  free_matrix(net.output_layer);

  free_matrix(net.input_weights);
  free_matrix(net.input_bias);

  free_matrix(net.hidden_weights);
  free_matrix(net.hidden_bias);
}
