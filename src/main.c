#include "main.h"

void help()
{
  printf("HELP : \n");
  printf("  --XOR number : This function will start the XOR neural network (proof of concept)\n");
  printf("  --OCR \"path\" : This function will start the OCR neural network\n");
}

int main(int argc, char *argv[])
{
  if(argc >= 2)
  {
    if(strcmp(argv[1], "--help") == 0)
    {
      help();
    }
    else if(strcmp(argv[1], "--XOR") == 0)
    {
      if (argc == 3)
      {
        int epoch = strtol(argv[2], NULL, 10); // convert string to int
        XOR(epoch);
      }
      else
      {
        XOR(-1);
      }
    }
    else if(strcmp(argv[1], "--OCR") == 0)
    {
      if (argc == 3)
      {
        OCR(argv[2]);
      }
    }
    else if(strcmp(argv[1], "--MATRIX") == 0)
    {
      test_matrix();
    }
  }
  else
  {
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
