#include "gtd.h"
#include "config.h"

void GTD(char* font_path)
{
  init_sdl();

  if(TTF_Init() == -1)
  {
    fprintf(stderr, "Failure to initalize TTF_Init : %s\n", TTF_GetError());
    exit(0);
  }

  TTF_Font* font = NULL;
  SDL_Color black = { 0, 0, 0, 1 };
  SDL_Surface* character_image = NULL;
  char* font_training_directory;
  char* filename = get_file_name(font_path);

  // if the training path doesn't exit, we create it
  if(folder_exists(TRAINING_DATA_PATH) != 0)
  {
    create_folder(TRAINING_DATA_PATH);
  }

  printf("> Loading the font %s...\n", filename);

  font = TTF_OpenFont(font_path, SIZE * SIZE);

  // if the font can't be loaded, next
  if(!font)
  {
    printf("Unable to load the font %s!\n", filename);
  }
  else
  {
    // if the font training path doesn't exit : we create the folder
    font_training_directory = create_path(TRAINING_DATA_PATH, filename);

    if(folder_exists(font_training_directory) != 0)
    {
      create_folder(font_training_directory);
    }

    size_t j = 0;
    char c = CHARACTERS[j];
    char* name;

    // for each character
    while (c)
    {
      // retrieve the image
      character_image = TTF_RenderGlyph_Solid(font, c, black);

      printf("%c => w: %d h: %d\n", c, character_image->w, character_image->h);

      // create a matrix from the image and resize it to 28x28
      Matrix* mat = resize_matrix(img_to_matrix(character_image), SIZE, SIZE);

      // free the inital character image
      SDL_FreeSurface(character_image);

      // print the 28x28 matrix
      print_matrix(mat);

      // initalize the name of the matrix file with the current character
      name = malloc(10 * sizeof(char));
      sprintf(name, "%d.m", (int) c);

      // save the matrix in memory
      save_matrix(mat, font_training_directory, name);

      // free the matrix name
      free(name);

      // free the matrix
      free_matrix(mat);

      // next character =>
      c = CHARACTERS[++j];
    }

    printf("Training sets of '%s' generated with success!\n", filename);
  }

  TTF_CloseFont(font);

  TTF_Quit();

  quit_sdl();
}
