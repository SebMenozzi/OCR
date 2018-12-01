#ifndef GTK_H
#define GTK_H
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

/* include le neural network + la détection des char + les tools + les traitements + la segmentation */

int create_window(int argc, char** argv);
void openfile(GtkButton* button, GtkLabel* text);
void loadimg(GtkButton* button, GtkImage* img);
void save_text(GtkButton* button, GtkTextBuffer* buffer);
int ocr(GtkButton* button, GtkTextBuffer* buffer);

#endif
