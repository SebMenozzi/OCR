#include "ocr.h"
#include "config.h"

void generate_training_data(SDL_Surface* image, int startline, int endline, int startcolum, int endcolum, size_t counter)
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

  Matrix* mat_resized = resize_matrix(mat, SIZE, SIZE);

  char* name = malloc(10 * sizeof(char));

  sprintf(name, "%d.m", (int) CHARACTERS[counter - 1]);

  save_matrix(mat_resized, TRAINING_DATA_SEG_PATH, name);

  free_matrix(mat_resized);
  free_matrix(mat);
}

void GTD_FROM_SEG(char* training_data_path)
{
  if(folder_exists(TRAINING_DATA_SEG_PATH) != 0)
  {
    create_folder(TRAINING_DATA_SEG_PATH);
  }

  // load the image
  SDL_Surface* image = load_image(training_data_path);
  // put the image in grey
  greyscale(image);
  // put it in black and white
  black_and_white(image);
  // segmentation
  horizontal_course(image, generate_training_data);

  printf("Data set generated successfully from the image: %s\n", training_data_path);

  // free the image from memory
  SDL_FreeSurface(image);

  quit_sdl();
}
