#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "gtk.h"


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
    char *filename;
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
    gtk_label_set_text(label, filename);
    g_free(filename);
  }
  gtk_widget_destroy(dialog);
}

void save_text(GtkButton *button, GtkTextBuffer *buffer)
{

}

void create_window(int argc, char **argv)
{
  //initialization of variables
  GtkWidget *MainWindow = NULL;
  GtkWidget *label = NULL;
  builder = gtk_builder_new();

  //init gtk
  gtk_init(&argc, &argv);

  //get main window
  MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(G_OBJECT(MainWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  //personalization
  gtk_window_set_title(GTK_WINDOW(MainWindow), "MMGD OCR");
  gtk_window_set_default_size(GTK_WINDOW(MainWindow), 400, 300);
  gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);
  gtk_widget_show_all(MainWindow);
  gtk_main();

  //quit
  return EXIT_SUCCESS;
}
