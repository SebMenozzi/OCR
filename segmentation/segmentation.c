/*
**  SEGMENTATION
**  file: segmentation.c
**  description: file containing all that has to do with the segmentation
**  process
*/
#include "segmentation.h"
#include <err.h>

SDL_Surface* whole_segmentation(SDL_Surface* img)
{
  int lines[img->h];
  Line_Detection(img, lines);
  int height = img->h;
  int lines_cleaned[height];
  checklines(lines, height, lines_cleaned);
  int columns[(img->w) * 3];
  for (int x = 0; x < img->w * 3; x++)
    columns[x] = -1;
  char_detection(img, lines_cleaned, columns);
  int nb_letters = get_number_letters(img, columns);
  printf("This image has %i letters\n", nb_letters);
  int nb_lines = get_number_lines(img, lines_cleaned);
  printf("It also has %i lines, according to my great intellect.\n", nb_lines);
  struct letter **l = create_letter_list(img, lines_cleaned, columns);
  double resized_inputs[256];
  space_mng(l, nb_letters);
  //for (int i = 0; i < 20; i++)
  //   print_letter(l[i]);
  size_t f = 49;
  resizePixels(l[f]->mat, resized_inputs, l[f]->width,
      l[f]->height, 16, 16);
  int max = l[f]->height > l[f]->width ? l[f]->height : l[f]->width;
  for (int n = 0; n < max; n++)
  {
    for (int j = 0; j < max; j++)
    {
      printf("%d", (int)l[f]->mat[j + n * max]);
    }
    printf("|\n");
  }
  printf("\n");
  for (int n = 0; n < 16; n++)
  {
    for (int j = 0; j < 16; j++)
    {
      printf("%d",(int)resized_inputs[j + n * 16]);
    }
    printf("|\n");
  }
  printf("\n");
  /*double idek [1024];
  center_letter(l[0], idek);
  for (int n = 0; n < 32; n++)
  {
    for (int j = 0; j < 32; j++)
    {
      printf("| %f ",idek[j + n * 32]);
    }
    printf("|\n");
  }
  printf("\n");*/
  return(text_blocks(img, 1, lines_cleaned, columns));
}

void resizePixels(double pixels[], double res[], int w1,int h1,int w2,int h2)
{
  // EDIT: added +1 to account for an early rounding problem
  //int x_ratio = (int)((w1<<16) / w2)+1 ;
  //int y_ratio = (int)((h1<<16) / h2)+1 ;
  double x_ratio = w1/(double)w2 ;
  double y_ratio = h1/(double)h2 ;
  int x2;
  int y2;
  for (int i = 0; i < w2; i++)
  {
    for (int j = 0; j < h2; j++)
    {
      x2 = (int) (j * x_ratio);
      y2 = (int) (i * y_ratio);
      res[(i * h2) + j] = pixels[(y2 * h1) + x2];
    }
  }
}

void center_letter(struct letter *src, double dst[])
{
  int bot_x = -1, bot_y = -1;
  for(int k = 0; k < 32; k++)
  {
    for(int l = 0; l < 32; l++)
    {
      if((src->mat[k + l * 32] == 0) && (bot_x == -1))
        bot_x = k;
      if((src->mat[l + k * 32] == 0) && (bot_y == -1))
        bot_y = k;
    }
  }
  int start_x = (32 - bot_x) / 2;
  int start_y = (32 - bot_y) / 2;
  for(int i = 0; i < src->width; i++) {
    for(int j = 0; j < src->height; j++) {
      dst[(start_x + i) + (start_y + j) * 32] = src->mat[(bot_x + i)
        + (bot_y + j) * 32];
    }
  }
}

int Line_Detection(SDL_Surface* img, int list_lines[])
{
  Uint32      pxl;
  Uint8       pxlcolor;
  for (int x = 0; x < img->h; x++)
    list_lines[x] = -1;
  int         i = 0; //list index
  int         prev_pxl = 0;
  for (int y = 0; y < img->h; y++)
  {
    for (int x = 0; x < img->w; x++)
    {
      pxl = getpixel(img, x, y);
      SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
      if (pxlcolor == 0)
      {
        if(prev_pxl == 1) //is previous pixel black?
        {
          list_lines[y] = 1;
          i++;
          break;
        }
        else
          prev_pxl = 1;
      }
      else
        prev_pxl = 0;
    }
  }
  return list_lines[img->h];
}


//removes lines from list when less than 5 consecutive line
int checklines(int l[], int nb_elts, int res[])
{
  for (int x = 0; x < nb_elts; x++)
    res[x] = -1;
  int consecutive_lines = 0;
  int top = 0;
  int bot = 0;
  for (int index = 0; index < nb_elts; index++)
  {
    if (l[index] == 1)
    {
      if (l[index] == l[index+1] && top == 0)
      {
        top = index;
        consecutive_lines++;
      }
      else if (l[index] == l[index+1] && top != 0)
        //top already found, continue onwards to find bot
      {
        consecutive_lines++;
        continue;
      }
      else // line is not followed by any other
      {
        if (l[index] == l[index-1] && bot == 0)
          //it's the last of a sequence (bot of letter)
        {
          bot = index;
          consecutive_lines++;
        }
        else if (l[index] == l[index-1] && bot != 0)
          //it's the last of a sequence (bot of letter)
        {
          consecutive_lines++;
          continue;
        }
        else
        {
          consecutive_lines = 0;
          continue; //ignores line for res (line is noise.)
        }
      }

      if (consecutive_lines >= 6)
      {
        res[top] = 1;
        res[bot] = 2;
        top = 0;
        bot = 0;
        consecutive_lines = 0;
      }
    }
  }
  return *res;
}

void char_detection(SDL_Surface* img, int list[], int res[])
{
  int black = 0;
  Uint8 pxlcolor;
  Uint32 pxl;
  int column_list_index = 0;
  int top_of_char_line_index = 0;
  int letter = 0;
  for (int i = 0; i < img->h; i++) //Goes through the line list
  {
    if (list[i] == 1) //We found the top of a char line
      top_of_char_line_index = i;
    if (list[i] == 2)
    {
      for (int x = 0; x < img->w; x++)
      {
        for (int y = top_of_char_line_index; y < i; y++)
        {
          pxl = getpixel(img,x,y);
          SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
          if (pxlcolor == 0)
            black = 1;
        }
        if (black == 1 && letter == 0)
        {
          // Warnx("column_list_index is :%d\n",column_list_index);
          letter = 1;
          res[column_list_index] = x;
          column_list_index++;
        }
        else if (black == 0 && letter == 1)
        {
          // Warnx("column_list_index is :%d\n",column_list_index);
          letter = 0;
          res[column_list_index] = x;
          //res[column_list_index + 1] = -1;
          column_list_index += 1;//2;
        }
        black = 0;
      }
      res[column_list_index] = -42; //EOL char
      column_list_index++;
    }
  }
}

SDL_Surface* text_blocks(SDL_Surface* img, int scale, int lines[], int cols[])
  /*
   ** Displays text blocks, depending on scale.
   ** 1: boxes around each letter
   ** 2: boxes around each word
   ** 3: boxes around each paragraph
   */
{
  if (scale == 1)
    return box_letters(img, lines, cols);
  else
    return img;
}

struct letter** create_letter_list(SDL_Surface* img, int lines[], int cols[])
{ //Boxes every letter of the text
  struct letter **list = malloc(sizeof(struct letter)
      * get_number_letters(img, cols));
  int y;
  //int tmp; //To not go to next line when we check for top of letters
  int index = 0;
  Uint8 pxlcolor;
  Uint32 pxl;
  int index_list_letter = 0;
  for (y = 0; y < img->h; y++)
  {
    if (lines[y] == 2)
    {
      for (; cols[index] != -42; )
      {
        int stop_checking = 0;
        for (int tmp_y = y; stop_checking != 1; tmp_y--)
        {
          for (int check_x = cols[index]; check_x < cols[index + 1]; check_x++)
          {
            pxl = getpixel(img, check_x, tmp_y);
            SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
            if (pxlcolor == 0)
            {
              struct letter* l = init_letter(cols[index], cols[index+1],
                  tmp_y + 1, img);
              list[index_list_letter] = l;
              index_list_letter++;
              stop_checking = 1;
              index += 2;
              break;
            }
          }
        }
      }
      list[index_list_letter - 1]->new_line = 1;
      index++;
    }
  }
  return list;
}


SDL_Surface* box_letters(SDL_Surface* img, int lines[], int cols[])
{ //Boxes every letter of the text
  int y;
  int tmp; //To not go to next line when we check for top of letters
  int index = 0;
  Uint8 pxlcolor;
  Uint32 pxl;
  for (y = 0; y < img->h; y++)
  {
    if (lines[y] == 1)
    {
      tmp = index;
      for (; cols[tmp] != -42; )
      {
        int keep_checking = 1;
        for (int tmp_y = y; keep_checking; tmp_y++)
        {
          for (int check_x = cols[tmp]; check_x < cols[tmp + 1]; check_x++)
          {
            pxl = getpixel(img, check_x, tmp_y);
            SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
            if (pxlcolor == 0)
            {
              draw_line(img, cols[tmp], cols[tmp + 1], tmp_y - 1);
              keep_checking = 0;
              tmp += 2;
              break;
            }
          }
        }
      }
    }
    if (lines[y] == 2)
    {
      for (; cols[index] != -42; )
      {
        int stop_checking = 0;
        for (int tmp_y = y; stop_checking != 1; tmp_y--)
        {
          for (int check_x = cols[index]; check_x < cols[index + 1]; check_x++)
          {
            pxl = getpixel(img, check_x, tmp_y);
            SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
            if (pxlcolor == 0)
            {
              draw_line(img, cols[index], cols[index + 1], tmp_y);
              stop_checking = 1;
              index += 2;
              break;
            }
          }
        }
      }
      index++;
    }
  }
  return img;
}

SDL_Surface* draw_line(SDL_Surface *img, int start_x, int end_x, int y)
{ //Draws a line on img, at height y, between points s_x and end_x
  for (; start_x < end_x; start_x++)
    putpixel(img, start_x, y, SDL_MapRGB(img->format, 255, 0, 0));
  return (img);
}

SDL_Surface* draw_column(SDL_Surface *img, int start_y, int end_y, int x)
{ //Draws a column on img, at width x, between points s_y and end_y
  for (; start_y < end_y; start_y++)
    putpixel(img, x, start_y, SDL_MapRGB(img->format, 255, 0, 0));
  return (img);
}


int get_number_letters(SDL_Surface *img, int cols[])
{
  int count_letters = 0;
  int tmp;
  int count_it = 1;
  for (tmp = 0; tmp < img->w * 3; tmp++)
  {
    if (cols[tmp] < 0)
      continue;
    if (count_it == 1)
    {
      count_letters++;
      count_it = 0;
    }
    else
      count_it = 1;
  }
  return count_letters;
}

int get_number_lines(SDL_Surface* img, int lines[])
{
  int count_lines = 0;
  int tmp;
  for (tmp = 0; tmp < img->h; tmp++)
    if (lines[tmp] == 2)
      count_lines++;
  return count_lines;
}

struct letter* init_letter(int topleft_x, int botright_x, int botright_y,
    SDL_Surface* img)
{
  struct letter* l = malloc(sizeof(struct letter));
  int line_has_black = 1;
  Uint32 pxl;
  Uint8 pxlcolor;
  int going_up;
  for (going_up = botright_y - 1; line_has_black != 0; going_up--)
  {
    line_has_black = 0;
    for (int tmp = topleft_x; tmp < botright_x; tmp++)
    {
      pxl = getpixel(img, tmp, going_up);
      SDL_GetRGB(pxl, img->format, &pxlcolor, &pxlcolor, &pxlcolor);
      if (pxlcolor == 0)
      {
        line_has_black = 1;
        break;
      }
    }
  }
  int topleft_y = going_up + 1;
  l->space_after = 0;
  l->new_line = 0;
  l->coord_x[0] = topleft_x;
  l->coord_x[1] = botright_x;
  l->coord_y[0] = topleft_y+1;
  l->coord_y[1] = botright_y /*+ 1*/;
  l->height = l->coord_y[1] - l->coord_y[0];
  l->width = l->coord_x[1] - l->coord_x[0];
  binarize_letter(img, l);
  return l;
}

void binarize_letter(SDL_Surface* img, struct letter* l)
{
  Uint8 r, g, b;
  int height = l->height;
  int width = l->width;
  int max = height > width ? height : width;
  double *mat = calloc(max * max, sizeof(double));
  for(int i = l->coord_y[0]; i < l->coord_y[1]; i++)
  {
    for (int j = l->coord_x[0]; j < l->coord_x[1]; j++)
    {
      SDL_GetRGB(getpixel(img, j, i),img->format,&r,&g,&b);
      if (r == 0)
        mat[(j - l->coord_x[0]) + (i - l->coord_y[0]) * max] = 1.0;
      else
        mat[(j - l->coord_x[0]) + (i - l->coord_y[0]) * max] = 0.0;
    }
  }
  l->mat = mat;
}

int threshold(struct letter **list_let, int len)
{
  int histo[50];
  for (int i = 0; i < 50; i++)
    histo[i] = 0;
  for(int i = 1; i < len; i++)
    if (list_let[i]->coord_x[0] - list_let[i - 1]->coord_x[1] >= 0)
      histo[list_let[i]->coord_x[0] - list_let[i - 1]->coord_x[1]] += 1;
  int l_th = 0;
  int h_th = 49;
  int l = 1;
  int fo = 1;
  int nfo = 1;
  int h = 1;
  for(size_t i = 1; i < 50; i++)
  {
    int check1 = histo[i] != 0;
    int check2 = histo[50 -i] != 0;
    if (h && check2)
    {
      h_th -= 1;
      fo = 0;
    }
    else
    {
      if (fo)
        h_th -= 1;
      else
        h = 0;
    }
    if (l && check1)
    {
      l_th += 1;
      nfo = 0;
    }
    else
    {
      if (nfo)
        l_th += 1;
      else
        l = 0;
    }
  }
  return (l_th + (h_th - l_th)/2);
}

void space_mng(struct letter **list_let, int nb_let)
{
  int th = threshold(list_let, nb_let);
  for (int i = 1; i < nb_let; i++)
  {
    if(list_let[i]->coord_x[0] - list_let[i-1]->coord_x[1] >= th)
      list_let[i]->space_after = 1;
  }
}

void print_letter(struct letter *l)
{
  printf("l->new_line = %i\n", l->new_line);
  printf("l->space_after = %i\n", l->space_after);
  printf("l->coord_x[0] = %i\n", l->coord_x[0]);
  printf("l->coord_x[1] = %i\n", l->coord_x[1]);
  printf("l->coord_y[0] = %i\n", l->coord_y[0]);
  printf("l->coord_y[1] = %i\n", l->coord_y[1]);
  printf("l->height = %i\n", l->height);
  printf("l->width = %i\n\n", l->width);
}
