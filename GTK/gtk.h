#ifndef GTK_H
#define GTK_H
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
/* include le neural network + la détection des char + les tools + les traitements + la segmentation */

void create_window(int argc, char **argv);
void openfile(GtkButton *button, GtkLabel *text);
void save_text(GtkButton *button, GtkTextBuffer *buffer);
