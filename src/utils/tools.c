#include "tools.h"

char* create_path(char* directory, char* name)
{
  char* fullpath;
  fullpath = malloc(strlen(directory) + strlen("/") + strlen(name) + 1);
  strcpy(fullpath, directory); // copy directory in fullpath
  strcat(fullpath, "/"); // add "/"
  strcat(fullpath, name); // add the name
  return fullpath;
}

double random_value() // between -1 and 1
{
  return 2.0f * rand() / RAND_MAX - 1;
}

float sigmoid(float x) // sigmoid function
{
  return 1.0 / (1.0 + exp(-x));
}

float sigmoid_prime(float x) // derivative of sigmoid function
{
  return x * (1.0 - x);
}

int create_folder(char* path)
{
  int error = 0;
  #if defined(_WIN32)
    error = _mkdir(path);
  #else
    error= mkdir(path, 0733);
  #endif
  return error;
}

int folder_exists(char* path)
{
  struct stat st;
  return stat(path, &st);
}

char* get_file_name(char* path)
{
  for(size_t i = strlen(path) - 1; i; i--)
  {
    if (path[i] == '/')
    {
      return &path[i + 1];
    }
  }
  return path;
}

void rmtree(const char path[])
{
  size_t path_len;
  char *full_path;
  DIR *dir;
  struct stat stat_path, stat_entry;
  struct dirent *entry;

  // stat for the path
  stat(path, &stat_path);

  // if path does not exists or is not dir - exit with status -1
  if (S_ISDIR(stat_path.st_mode) == 0) {
    fprintf(stderr, "%s: %s\n", "Is not directory", path);
    exit(-1);
  }

  // if not possible to read the directory for this user
  if ((dir = opendir(path)) == NULL) {
    fprintf(stderr, "%s: %s\n", "Can`t open directory", path);
    exit(-1);
  }

  // the length of the path
  path_len = strlen(path);

  // iteration through entries in the directory
  while ((entry = readdir(dir)) != NULL) {
    // skip entries "." and ".."
    if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        continue;

    // determinate a full path of an entry
    full_path = calloc(path_len + strlen(entry->d_name) + 1, sizeof(char));
    strcpy(full_path, path);
    strcat(full_path, "/");
    strcat(full_path, entry->d_name);

    // stat for the entry
    stat(full_path, &stat_entry);

    // recursively remove a nested directory
    if (S_ISDIR(stat_entry.st_mode) != 0) {
      rmtree(full_path);
      continue;
    }

    // remove a file object
    if (unlink(full_path) == 0)
      printf("Removed a file: %s\n", full_path);
    else
      printf("Can`t remove a file: %s\n", full_path);
  }

  // remove the devastated directory and close the object of it
  if (rmdir(path) == 0)
    printf("Removed a directory: %s\n", path);
  else
    printf("Can`t remove a directory: %s\n", path);

  closedir(dir);
}

void add(char **s, char c)
{
  size_t len = strlen(*s);
  char *str = realloc(*s,(len + 2) * sizeof(char));
  *(str + len) = c;
  *(str + len + 1) = '\0';
  *s = str;
}

void add_character(const char *filepath, const char character)
{
  FILE* file = fopen(filepath, "a");
  // convert char into string
  char data[2];
	data[0] = character;
	data[1] = '\0'; 	//string always ends with a null character

  if (file != NULL)
  {
    fputs(data, file);
    fclose(file);
  }
}

int load_file(const char *filename, char **result)
{
	size_t size = 0;
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		*result = NULL;
		return -1; // -1 means file opening fail
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	*result = (char*) malloc(size + 1);
	if (size != fread(*result, sizeof(char), size, f))
	{
		free(*result);
		return -2; // -2 means file reading fail
	}
	fclose(f);
	(*result)[size] = 0;
	return size;
}
