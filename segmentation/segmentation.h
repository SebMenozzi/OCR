/*
 *  SEGMENTATION
 *  file: segmentation.h
 *  description: header for segmentation
 */

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_
#include "../mysdl/mysdl.h"

struct letter
{
  int new_line;
  int space_after;
  int coord_x [2];
  int coord_y [2];
  int height; //int coord_topleft
  int width; //int coord_botright
  double *mat; //Contains the binarized height*width letter in 0 and 1s
};

struct letter* init_letter(int topleft_x, int botright_x, int botright_y,
    SDL_Surface* img);
void binarize_letter(SDL_Surface* img, struct letter* l);
void char_detection(SDL_Surface* img, int list[], int res[]);
SDL_Surface* Display_Character_Boxes(SDL_Surface* img, int startlines[],
        int columns[]);
int Line_Detection(SDL_Surface* img, int lines[]);
SDL_Surface* DisplayLines (SDL_Surface* img, int y[], int nb_elts);
SDL_Surface* text_blocks(SDL_Surface* img, int scale, int lines[], int cols[]);
SDL_Surface* box_letters(SDL_Surface* img, int lines[], int cols[]);
SDL_Surface* draw_line(SDL_Surface* img, int start_x, int end_x, int y);
SDL_Surface* draw_column(SDL_Surface* img, int start_y, int end_y, int x);
int checklines(int l[], int nb_elts, int res[]);
SDL_Surface* whole_segmentation(SDL_Surface* img);
int get_number_letters(SDL_Surface* img, int cols[]);
int get_number_lines(SDL_Surface* img, int lines[]);
struct letter **create_letter_list(SDL_Surface* img, int lines[], int cols[]);
void print_letter(struct letter *l);
struct letter_bin *resize_image(double inputs[], double resized_inputs[],
    int width , int height);
int threshold(struct letter **list_let, int len);
void space_mng(struct letter **list_let, int nb_let);
void resizePixels(double pixels[], double res[], int w1,int h1,int w2,int h2);
void center_letter(struct letter *src, double dst[]);
#endif
