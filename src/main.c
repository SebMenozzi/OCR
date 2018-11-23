#include "main.h"
#include "mnist.h"
#include "matrix.h"

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
    else if(strcmp(argv[1], "--XOR") == 0)
    {
      XOR();
    }
    else if(strcmp(argv[1], "--OCR") == 0)
    {
      OCR(argv[2]);
    }
    else if(strcmp(argv[1], "--MATRIX") == 0)
    {
      test_matrix();
    }
    else if (strcmp(argv[1], "--MNIST") == 0)
    {
      /*
      // call to store mnist in array
      load_mnist();

      // print pixels of first data in test dataset
      for (int i = 0; i < 784; i++) {
          //printf("%1.1f ", train_image[0][i]);
          //if ((i+1) % 28 == 0) putchar('\n');
      }

      // print first label in test dataset
      //printf("label: %d\n", train_label[0]);
      */
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
