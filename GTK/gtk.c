#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "gtk.h"

gchar *filename = "";

void openfile(GtkButton *button, GtkLabel *text)
{
  GtkWidget *dialog;
  GtkLabel *label = text;

  dialog = gtk_file_chooser_dialog_new("Open Image", parent_window,
                                        GTK_FILE_CHOOSER_ACTION_OPEN,
                                        "Open", GTK_RESPONSE_ACCEPT,
                                        "Cancel", GTK_RESPONSE_CANCEL,
                                        NULL);
  if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
  {
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    gtk_label_set_text(label, filename);
    //g_free(filename); ??? jsp si c'est nécessaire
  }
  gtk_widget_destroy(dialog);
}

//besoin du paramètre GtkButton à confirmer
void loadimg(GtkButton *button, GtkImage *img)
{
  /*UNUSED(button); */

  //IF EMPTY FILENAME, DON'T DO ANYTHING
  /* if(strcmp(filename, "") == 0)
  {
    return;
  } */
  //IF IMG TOO BIG : RESIZE BEFORE LOADING

/*  if (img->w > 550 && img->h > 400)
  {
    SDL_Surface *resizedimg = Resize(img);
    SDL_SaveBMP(resizedimg, "resized_image");
    gtk_image_set_from_file(GTK_IMAGE(resizedimg), "resized_image");
  } */

  SDL_Surface *img = IMG_Load((char*) filename);
  if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());
  gtk_image_set_from_file(GTK_IMAGE(img), filename);

}

void ocr(GtkButton *button, GtkTextBuffer *buffer)
{
  //IF EMPTY FILENAME, DON'T DO ANYTHING
  /* if(strcmp(filename, "") == 0)
  {
    return 1;
  } */

  /* UNUSED(button); */

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *image = IMG_Load((char*) filename);
  if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

  //IMG PRE TREATMENTS
  greyscale(image);

  black_and_white(image);
  //black_and_white2(image);

  //SEGMENTATION

  SDL_QUIT();
  return EXIT_SUCCESS;

}

void save_text(GtkButton *button, GtkTextBuffer *buffer)
{

}

void create_window(int argc, char **argv)
{
  //initialization of variables
  GtkWidget *MainWindow;
  GtkWidget *label;

  //init gtk
  gtk_init(&argc, &argv);

  //get main window
  MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(G_OBJECT(MainWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  //personalization
  gtk_window_set_title(GTK_WINDOW(MainWindow), "MMGD OCR");
  gtk_window_set_default_size(GTK_WINDOW(MainWindow), 550, 400);
  gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);
  gtk_widget_show_all(MainWindow);
  gtk_main();

  //quit
  return EXIT_SUCCESS;
}
