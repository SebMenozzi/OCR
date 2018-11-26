#include "xor.h"

// training data
double training_data[4][2] =
{
  { 0, 0 },
  { 0, 1 },
  { 1, 0 },
  { 1, 1 }
};
// target
double anwser_data[4] = { 0, 1, 1, 0 };

void print_xor_result(NeuralNetwork network)
{
  double output_0_0 = get_network_result(network, training_data[0])->values[0];
  double output_0_1 = get_network_result(network, training_data[1])->values[0];
  double output_1_0 = get_network_result(network, training_data[2])->values[0];
  double output_1_1 = get_network_result(network, training_data[3])->values[0];

  printf("+-------------------+\n");
  printf("| 0 | 0 | 0 => %.2f |\n", output_0_0);
  printf("| 0 | 1 | 1 => %.2f |\n", output_0_1);
  printf("| 1 | 0 | 1 => %.2f |\n", output_1_0);
  printf("| 1 | 1 | 0 => %.2f |\n", output_1_1);
  printf("+-------------------+\n");
}

void XOR(int epoch)
{
  double inputs[2];
  double target[1];

  // nb_input, nb_hidden, nb_output
  NeuralNetwork network = new_network(2, 10, 1);

  if (epoch > 0)
  {
    // train the network x times
    for (int i = 0; i < epoch; ++i)
    {
      // for each training data
      for (size_t j = 0; j < 4; ++j)
      {
        inputs[0] = training_data[j][0];
        inputs[1] = training_data[j][1];
        forward_propagate(network, inputs);

        target[0] = anwser_data[j];
        back_propagate(network, target, 0.5, 0.9); // network, target, learning_rate, momentum

        print_error_rate(network);
      }
    }
  }
  else
  {
    // load the network from memory
    load_network(network, "data/xor");
  }

  print_xor_result(network);

  save_network(network, "data/xor");
  free_network(network);
}
