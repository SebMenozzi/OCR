#include "train_ocr.h"
#include "config.h"

void TRAIN_OCR(int epoch)
{
  // nb_input, nb_hidden, nb_output
  NeuralNetwork network = new_network(SIZE * SIZE, NB_HIDDEN, NB_CHARACTERS);
  char *fonts[] = { "from_segmentation",
                    //"arial-black.ttf",
                    //"arial.ttf",
                    //"avant-garde.ttf",
                    //"bookman.ttf",
                    //"calibri.ttf",
                    //"droid-sans.ttf",
                    //"garamond.ttf",
                    //"georgia.ttf",
                    //"helvetica.ttf",
                    //"lato.ttf",
                    //"open-sans.ttf",
                    //"palatino.ttf",
                    //"pt-sans.ttf",
                    //"source-sans-pro.ttf",
                    //"tahoma.ttf",
                    //"times.ttf",
                    //"verdana.ttf"
                  };

  if (epoch > 0)
  {
    char* font_training_directory;
    char* name;
    Matrix* character = new_matrix(SIZE, SIZE);
    int e, i, j;

    for (e = 0; e < epoch; ++e)
    {
      // for each font
      for (i = 0; i < 1; ++i)
      {
        font_training_directory = create_path(TRAINING_DATA_PATH, fonts[i]);

        // for each character
        for (j = 0; j < NB_CHARACTERS; ++j)
        {
          name = malloc(10 * sizeof(char));
          sprintf(name, "%d.m", (int) CHARACTERS[j]);

          load_matrix(character, font_training_directory, name);

          printf("%c => %s\n", CHARACTERS[j], fonts[i]);

          print_matrix(character);

          // transform matrix 28x28 into 784x1
          //character = square_matrix_to_column(character);

          forward_propagate(network, character->values);

          Matrix* target = new_matrix(NB_CHARACTERS, 1);
          target->values[j]  = 1.0;

          back_propagate(network, target->values, 0.5, 0.3); // network, target, learning_rate, momentum

          //print_matrix_double(network.output_layer);

          print_error_rate(network);
        }
      }
    }

    save_network(network, "data/ocr");
  }
}
