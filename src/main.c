#include "main.h"

void help()
{
    printf("HELP : \n");
    printf("  --XOR  This function will start the XOR neural network (proof of concept)\n");
    printf("  --OCR  This function will start the OCR neural network\n");
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
            OCR();
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
