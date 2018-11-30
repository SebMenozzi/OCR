#include "ocr.h"
#include "config.h"

void extract_characters(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum, size_t counter)
{
  size_t height = endline - startline,
         width = endcolum - startcolum + 1;

  Matrix* mat = new_matrix(height, width);

  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      mat->values[y * width + x] = get_value_pixel(image, startcolum + x, startline + y + 1);
    }
  }

  Matrix* inputs = resize_matrix(mat, SIZE, SIZE);

  // nb_input, nb_hidden, nb_output
  NeuralNetwork network = new_network(SIZE * SIZE, NB_HIDDEN, NB_CHARACTERS);

  // load the network from memory
  load_network(network, "data/ocr");

  print_matrix(inputs);

  forward_propagate(network, inputs->values);

  //print_matrix_double(network.output_layer);

  int max_position = 0;
  double maximum = network.output_layer->values[0];
  double value;
  int cursor = 0;

  // take the maximum in the output layer
  for (size_t r = 0; r < network.output_layer->rows; ++r)
  {
    for (size_t c = 0; c < network.output_layer->cols; ++c)
    {
      cursor = r * network.output_layer->cols + c;
      value = network.output_layer->values[cursor];

      if (value > maximum)
      {
        maximum = value;
        max_position = cursor;
      }
    }
  }
  // print the character
  printf("%zu => %c \n\n", counter, CHARACTERS[max_position]);

  // add character in output.txt
  add_character("data/output.txt", CHARACTERS[max_position]);
}

void OCR(char* file)
{
  init_sdl();

  // load the image
  SDL_Surface* image = load_image(file);
  // put the image in grey
  greyscale(image);
  // put it in black and white
  black_and_white(image);
  // segmentation
  horizontal_course(image, extract_characters);
  // free the image from memory
  SDL_FreeSurface(image);

  quit_sdl();
}
