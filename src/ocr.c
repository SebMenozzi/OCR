#include "ocr.h"

void OCR(char* file)
{
  init_sdl();

  SDL_Surface* image = load_image(file);
  greyscale(image);
  black_and_white(image);
  horizontal_course(image);

  // nb_input (28 * 28), nb_hidden, nb_output (number of characters : 26 * 2 => min and maj)
  NeuralNetwork network = new_network(784, 20, 52);

  // load the network from memory
  load_network(network, "data/ocr");

  SDL_FreeSurface(image);

  quit_sdl();
}
