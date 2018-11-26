#include "generate_training_data.h"

#define TRAINING_PATH "data/training_data"

void GENERATE_TRAINING_DATA(char* directory)
{
  init_sdl();

  int counter = 0, i = 0;
  struct dirent *dir;  // Pointer for directory entry

  // opendir() returns a pointer of DIR type.
  DIR *d = opendir(directory);

  if (d == NULL)  // opendir returns NULL if couldn't open directory
  {
    printf("Could not open current directory\n");
    exit(1);
  }
  else
  {
    while ((dir = readdir(d)) != NULL)
    {
      if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
      {
        counter++;
      }
    }
    rewinddir(d);

    char* files_list[counter];

    //Put file names into the array
    while((dir = readdir(d)) != NULL)
    {
      if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
      {
        files_list[i] = (char*) calloc(strlen(dir->d_name) + 1, sizeof(char));
        strncpy(files_list[i], dir->d_name, strlen(dir->d_name));
        i++;
      }
    }

    rewinddir(d);

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Failure to initalize TTF_Init : %s\n", TTF_GetError());
        exit(0);
    }

    TTF_Font *font = NULL;
    SDL_Color black = {0, 0, 0, 1};
    SDL_Surface* character_image = NULL;
    char* font_path;
    char* font_training_directory;

    // if the training path doesn't exit, we create it
    if(folder_exists(TRAINING_PATH) != 0)
    {
      create_folder(TRAINING_PATH);
    }

    // for each font
    for(size_t i = 0; i < sizeof(files_list) / sizeof(files_list[0]); ++i)
    {
      printf("> Loading the font %s...\n", files_list[i]);

      // Load the font in the font directory
      font_path = create_path(directory, files_list[i]);

      font = TTF_OpenFont(font_path, 28);

      // if the font can't be loaded, next
      if(!font)
      {
        printf("Unable to load the font %s!\n", files_list[i]);
      }
      else
      {
        // if the font training path doesn't exit : we create the folder
        font_training_directory = create_path(TRAINING_PATH, files_list[i]);

        if(folder_exists(font_training_directory) != 0)
        {
          create_folder(font_training_directory);
        }

        // 11 special characters + 10 digits + 52 letters => 73
        char characters[] = ")(*+-,.:;!?0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

        size_t j = 0;
        char c = characters[j];
        char* name;

        // for each character
        while (c)
        {
          // retrieve the image
          character_image = TTF_RenderGlyph_Solid(font, c, black);

          printf("%c => w: %d h: %d\n", c, character_image->w, character_image->h);

          // create a matrix from the image and resize it to 28x28
          Matrix* mat = resize_matrix(img_to_matrix(character_image), 28, 28);

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
          c = characters[++j];
        }

        printf("Training sets of '%s' generated with success!\n", files_list[i]);
      }

      TTF_CloseFont(font);
    }

    TTF_Quit();
  }

  quit_sdl();
}
