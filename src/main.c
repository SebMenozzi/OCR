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
      double inputs[] = { 0, 1 };
      NeuralNetwork network = new_network(2, 3, 1, 0.5, 0.9);
      printf("Input: \n");
      print_matrix(network.input_layer);
      print_matrix(network.input_weights);
      print_matrix(network.input_bias);
      printf("-------\n");
      printf("Hidden: \n");
      print_matrix(network.hidden_layer);
      print_matrix(network.hidden_weights);
      print_matrix(network.hidden_bias);
      printf("-------\n");

      forward_propagate(network, inputs);

      print_matrix(network.input_layer);
      print_matrix(network.hidden_layer);
      print_matrix(network.output_layer);

      free_network(network);
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
