#include "train_ocr.h"

void TRAIN_OCR(int epoch)
{
  // nb_input (28 * 28), nb_hidden, nb_output (number of characters : 26 * 2 => min and maj)
  NeuralNetwork network = new_network(784, 20, 52);

  printf("%d\n", epoch);

  /*
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
    load_network(network, "data/ocr");
  }
  */

  save_network(network, "data/ocr");
  free_network(network);
}
