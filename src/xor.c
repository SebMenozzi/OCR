#include "xor.h"

// training data
double training_data[4][2] = {
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

void XOR(size_t epoch)
{
  double inputs[2];
  double target[1];

  // nb_input, nb_hidden, nb_output, learning_rate
  NeuralNetwork network = new_network(2, 10, 1, 0.5);

  // train the network x times
  for (size_t i = 0; i < epoch; i++)
  {
    // for each training data
    for (size_t j = 0; j < 4; j++)
    {
      inputs[0] = training_data[j][0];
      inputs[1] = training_data[j][1];
      forward_propagate(network, inputs);

      target[0] = anwser_data[j];
      back_propagate(network, target);
    }
  }
  print_xor_result(network);

  save_network(network);
  free_network(network);
}
