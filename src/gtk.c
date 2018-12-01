#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h> 
#include "gtk.h"
#include "ocr.h"
#include "utils/tools.h"

typedef struct
{
  GtkBuilder* builder;
  gpointer user_data;
} SGlobalData;

GtkWidget* MainWindow;
GtkWidget* currentWindow;
gchar* filename = "";
SGlobalData data;
GtkWidget* textview;
GtkTextBuffer* buffer;

void callback_ok()
{
  gtk_dialog_response(GTK_DIALOG(currentWindow), GTK_RESPONSE_ACCEPT);
}


void callback_cancel()
{
  gtk_dialog_response(GTK_DIALOG(currentWindow), GTK_RESPONSE_CLOSE);
}


void callback_openfile()
{
  GtkWidget* dialog = NULL;

  dialog = GTK_WIDGET(gtk_builder_get_object(data.builder, "Dialog"));
  currentWindow = dialog;

  if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
  {
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
  }
  //printf("%s\n", mydata->filename);
  gtk_widget_hide(dialog);
}


void callback_ocr()
{
  OCR(filename);
}

void callback_loadtext(GtkButton* button, gpointer data)
{
  char* output;
  int size = load_file("data/output.txt", &output);
  if (size < 0)
  {
    printf("Can't read output.txt!\n");
  }

  gtk_text_buffer_set_text(buffer, output, strlen(output));
}

int create_window(int argc, char** argv)
{

    //init gtk
    gtk_init(&argc, &argv);

    data.builder = gtk_builder_new();

    gtk_builder_add_from_file(data.builder, "main_ui.glade", NULL);

	textview = GTK_TEXT_VIEW(gtk_builder_get_object(data.builder, "textview"));
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
	gtk_text_buffer_set_text(buffer, "Load the image, launch the OCR treatment, then click on \"Open Text\" and see !", -1);
    
    gtk_builder_connect_signals(data.builder, &data);

    //get main window
    MainWindow = GTK_WIDGET(gtk_builder_get_object(data.builder, "MainWindow"));

    //personalization
    //gtk_window_set_title(GTK_WINDOW(MainWindow), "MMGD OCR");
    //gtk_window_set_default_size(GTK_WINDOW(MainWindow), 550, 400);
    //gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);
   
    gtk_widget_show_all(MainWindow);
    gtk_main();
}
