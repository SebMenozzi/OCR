#include "main.h"
#include "mnist.h"
#include "matrix.h"
#include "neural_network.h"

void help()
{
  printf("HELP : \n");
  printf("  --XOR  This function will start the XOR neural network (proof of concept)\n");
  printf("  --OCR \"path\" This function will start the OCR neural network\n");
}

int main(int argc, char *argv[])
{
  if(argc > 1)
  {
    if(strcmp(argv[1], "--help") == 0)
    {
      help();
    }
    /*
    else if(strcmp(argv[1], "--XOR") == 0)
    {
      XOR();
    }
    */
    else if(strcmp(argv[1], "--OCR") == 0)
    {
      OCR(argv[2]);
    }
    else if(strcmp(argv[1], "--MATRIX") == 0)
    {
      test_matrix();
    }
    else if (strcmp(argv[1], "--NET") == 0)
    {
      double inputs[] = { 1, 0 };
      double target[] = { 1 };

      /*
      // nb_input, nb_hidden, nb_output, learning_rate, momentum
      NeuralNetwork network = new_network(2, 10, 1, 0.5);

      for (size_t i = 0; i < 100; ++i)
      {
        forward_propagate(network, inputs);
        back_propagate(network, target);
        printf("\n");

        printf("Input: \n");
        print_matrix(network.input_layer);
        printf("Hidden: \n");
        print_matrix(network.hidden_layer);
        printf("Output: \n");
        print_matrix(network.output_layer);
        printf("-------\n");
      }

      save_network(network);

      free_network(network);
      */

      printf("\n--Reload Network--\n");

      NeuralNetwork network2 = new_network(2, 10, 1, 0.5);
      load_network(network2);

      for (size_t i = 0; i < 10; ++i)
      {
        forward_propagate(network2, inputs);
        back_propagate(network2, target);

        printf("Input: \n");
        print_matrix(network2.input_layer);
        printf("Hidden: \n");
        print_matrix(network2.hidden_layer);
        printf("Output: \n");
        print_matrix(network2.output_layer);
        printf("-------\n");
      }

      save_network(network2);

      free_network(network2);
    }
  }
  else {
    printf("#-----------#\n");
    printf("| MMGD TEAM |\n");
    printf("#-----------#\n\n");
    printf("BY\n");
    printf("- Marcheron Laure\n");
    printf("- Menozzi Sebastien\n");
    printf("- Goré Benjamin\n");
    printf("- Denglos Gauthier\n\n");
  }
  return EXIT_SUCCESS;
}
