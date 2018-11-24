#include "neural_network.h"

NeuralNetwork new_network(size_t nb_input, size_t nb_hidden, size_t nb_output, double learning_rate/*, double momentum*/)
{
  NeuralNetwork net;
  net.nb_input = nb_input;
  net.nb_hidden = nb_hidden;
  net.nb_output = nb_output;

  net.input_layer = new_matrix(nb_input, 1);
  net.hidden_layer = new_matrix(nb_hidden, 1);
  net.output_layer = new_matrix(nb_output, 1);

  net.input_hidden_weights = new_matrix(nb_input, nb_hidden);
  //net.delta_input_hidden_weights = new_matrix(nb_input, nb_hidden);
  net.input_hidden_bias = new_matrix(nb_hidden, 1);

  net.hidden_output_weights = new_matrix(nb_hidden, nb_output);
  //net.delta_hidden_weights = new_matrix(nb_hidden, nb_output);
  net.hidden_output_bias = new_matrix(nb_output, 1);

  net.target = new_matrix(nb_output, 1);

  net.delta_output = new_matrix(nb_output, 1);
  net.delta_hidden = new_matrix(nb_hidden, 1);

  // error rate initialized to 0
  net.mae_rate = 0;
  net.rmse_rate = 0;

  net.learning_rate = learning_rate;
  //net.momentum = momentum;

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
      net.input_hidden_weights->values[r * net.nb_hidden + c] = random_value();
    }
    net.input_hidden_bias->values[c] = random_value();
  }

  // initalize hidden weights and bias
  for (size_t c = 0; c < net.nb_output; ++c)
  {
    for (size_t r = 0; r < net.nb_hidden; ++r)
    {
      net.hidden_output_weights->values[r * net.nb_output + c] = random_value();
    }
    net.hidden_output_bias->values[c] = random_value();
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
      weight = net.input_hidden_weights->values[r * net.nb_hidden + c];
      layer = net.input_layer->values[r];

      sum += weight * layer;
    }
    bias = net.input_hidden_bias->values[c];
    net.hidden_layer->values[c] = sigmoid(sum + bias);
  }

  // Update output layer
  for (size_t c = 0; c < net.nb_output; ++c)
  {
    sum = 0.0;
    for (size_t r = 0; r < net.nb_hidden; ++r)
    {
      weight = net.hidden_output_weights->values[r * net.nb_output + c];
      layer = net.hidden_layer->values[r];

      sum += weight * layer;
    }
    bias = net.hidden_output_bias->values[c];
    net.output_layer->values[c] = sigmoid(sum + bias);
  }
}

void back_propagate(NeuralNetwork net, double* target)
{
  // we put the target
  net.target->values = target;

  //print_error_rate(net); // for debugging
  calculate_deltas(net);
  update_weights(net);
  update_bias(net);
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

void calculate_deltas(NeuralNetwork net)
{
  // Calulate cost function for output neurons
  double output, derivate, target;
  for (size_t r = 0; r < net.nb_output; ++r)
  {
    output = net.output_layer->values[r];
    derivate = sigmoid_prime(output);
    target = net.target->values[r];
    net.delta_output->values[r] = (target - output) * derivate;
  }

  // Calculate cost function for hidden neurons
  double sum, weight, delta, layer;
  for (size_t r = 0; r < net.nb_hidden; ++r)
  {
    sum = 0.0;
    for (size_t c = 0; c < net.nb_output; ++c)
    {
      weight = net.hidden_output_weights->values[r * net.nb_output + c];
      delta = net.delta_output->values[c];
      sum += weight * delta;
    }
    layer = net.hidden_layer->values[r];
    derivate = sigmoid_prime(layer);
    net.delta_hidden->values[r] = sum * derivate;
  }
}

void update_weights(NeuralNetwork net)
{
  double gradient, /*dweight,*/ delta, layer;

  // Weights between input and hidden layers
  for (size_t c = 0; c < net.nb_hidden; ++c)
  {
    for(size_t r = 0; r < net.nb_input; ++r)
    {
      delta = net.delta_hidden->values[c];
      layer = net.input_layer->values[r];
      //dweight = net.delta_input_hidden_weights->values[r * net.nb_hidden + c];
      gradient = delta * layer;
      net.input_hidden_weights->values[r * net.nb_hidden + c] += gradient * net.learning_rate;
      /*
      net.input_hidden_weights->values[r * net.nb_hidden + c] += gradient * net.learning_rate +
                                                          dweight * net.momentum;
      net.delta_input_hidden_weights->values[r * net.nb_hidden + c] = gradient * net.learning_rate;
      */
    }
  }

  // Weights between hidden and output layers
  for (size_t c = 0; c < net.nb_output; ++c)
  {
    for(size_t r = 0; r < net.nb_hidden; ++r)
    {
      delta = net.delta_output->values[c];
      layer = net.hidden_layer->values[r];
      //dweight = net.delta_hidden_weights->values[r * net.nb_output + c];
      gradient = delta * layer;
      net.hidden_output_weights->values[r * net.nb_output + c] += gradient * net.learning_rate;
      /*
      net.hidden_output_weights->values[r * net.nb_output + c] += gradient * net.learning_rate +
                                                           dweight * net.momentum;
      net.delta_hidden_weights->values[r * net.nb_output + c] = gradient * net.learning_rate;
      */
    }
  }
}

void update_bias(NeuralNetwork net)
{
  double delta;

  // Update input_hidden_bias
  for (size_t r = 0; r < net.nb_hidden; ++r)
  {
    delta = net.delta_hidden->values[r];
    net.input_hidden_bias->values[r] += delta * net.learning_rate;
  }

  // Update hidden_output_bias
  for (size_t r = 0; r < net.nb_output; ++r)
  {
    delta = net.delta_output->values[r];
    net.hidden_output_bias->values[r] += delta * net.learning_rate;
  }
}

void save_network(NeuralNetwork net, char* directory)
{
  save_matrix(net.input_hidden_weights, directory, "inputHidden.w");
  save_matrix(net.hidden_output_weights, directory, "hiddenOutput.w");
  save_matrix(net.input_hidden_bias, directory, "inputHidden.b");
  save_matrix(net.hidden_output_bias, directory, "hiddenOutput.b");
}

void load_network(NeuralNetwork net, char* directory)
{
  load_matrix(net.input_hidden_weights, directory, "inputHidden.w");
  load_matrix(net.hidden_output_weights, directory, "hiddenOutput.w");
  load_matrix(net.input_hidden_bias, directory, "inputHidden.b");
  load_matrix(net.hidden_output_bias, directory, "hiddenOutput.b");
}

void free_network(NeuralNetwork net)
{
  free_matrix(net.input_layer);
  free_matrix(net.hidden_layer);
  free_matrix(net.output_layer);

  free_matrix(net.input_hidden_weights);
  free_matrix(net.input_hidden_bias);

  free_matrix(net.hidden_output_weights);
  free_matrix(net.hidden_output_bias);

  free_matrix(net.delta_hidden);
  free_matrix(net.delta_output);

  free_matrix(net.target);
}

Matrix* get_network_result(NeuralNetwork net, double* inputs)
{
  forward_propagate(net, inputs);
  return net.output_layer;
}
