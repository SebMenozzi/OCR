#include "xor.h"
#include "ocr.h"
#include "ocr_ui.h"
#include "utils/matrix.h"
#include "train_ocr.h"
#include "gtd.h"
#include "gtd_from_seg.h"

void help()
{
  printf("HELP : \n");
  printf("  --XOR number : This function will start the XOR neural network (proof of concept)\n");
  printf("  --OCR \"path\" : This function will start the OCR neural network\n");
  printf("  --OCR_UI \"path\" : This function will start the OCR neural network with an UI\n");
  printf("  --GTD \"path_of_fonts\" : This function will generate a training data from a fonts directory\n");
  printf("  --TRAIN_OCR number : This function will train the OCR neural network with current the generated training data\n");
}

int main(int argc, char *argv[])
{
  // TODO: REFACTORING DIRTY CODE WITH TOO MANY REPETITIONS
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
    else if(strcmp(argv[1], "--OCR_UI") == 0)
    {
      if (argc == 3)
      {
        OCR_UI(argv[2]);
      }
    }
    else if(strcmp(argv[1], "--MATRIX") == 0)
    {
      test_matrix();
    }
    else if(strcmp(argv[1], "--TRAIN_OCR") == 0)
    {
      if (argc == 3)
      {
        int epoch = strtol(argv[2], NULL, 10); // convert string to int
        TRAIN_OCR(epoch);
      }
      else
      {
        TRAIN_OCR(-1);
      }
    }
    else if(strcmp(argv[1], "--GTD") == 0)
    {
      if (argc == 3)
      {
        GTD(argv[2]);
      }
    }
    else if(strcmp(argv[1], "--GTD_FROM_SEG") == 0)
    {
      if (argc == 3)
      {
        GTD_FROM_SEG(argv[2]);
      }
    }
  }
  else
  {
    printf("+-----------+\n");
    printf("| MMGD TEAM |\n");
    printf("+-----------+\n\n");
    printf("By\n");
    printf("- Marcheron Laure\n");
    printf("- Menozzi Sebastien\n");
    printf("- Goré Benjamin\n");
    printf("- Denglos Gauthier\n\n");
  }
  return EXIT_SUCCESS;
}
