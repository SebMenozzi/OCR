#include "ocr.h"
#include "config.h"

int old_startline = -1;
int old_startcolum = -1;
int old_endcolum = -1;

void extract_characters(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum, size_t counter)
{
  // deal with line break
  if (old_startline != -1 && startline - old_startline != 0) {
    add_character("data/output.txt", '\n');
  }
  else {
    // deal with spaces
    //printf("start: %d\n", startcolum - old_startcolum);
    //printf("end: %d\n", endcolum - old_endcolum);

    if (old_endcolum != -1 && endcolum - old_endcolum > 15 || startcolum - old_startcolum > 15) 
    {
      add_character("data/output.txt", ' ');
    }
  }

  old_startline = startline;
  old_startcolum = startcolum;
  old_endcolum = endcolum;

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

  //print_matrix(inputs);

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
  printf("%zu => %c \n", counter, CHARACTERS[max_position]);

  // add character in output.txt
  add_character("data/output.txt", CHARACTERS[max_position]);
}

void OCR(char* file)
{
  // clear the output
  remove("data/output.txt");

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

  char* output;
  int size;
  size = load_file("data/output.txt", &output);
	if (size < 0)
	{
		printf("Can't read output.txt!\n");
	}
  else
  {
    printf("%s\n", output);
  }
}
