#include "gio/gio.h"
#include "gmodule.h"
#include <gtk/gtk.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define UI_FILE_PATH "src/gui/paint-piet.ui"
#define WINDOW_ID "main_window"

G_MODULE_EXPORT void
print_hello (GtkWidget *widget, gpointer data)
{
	g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data)
{
	
	GtkBuilder *builder;


	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, UI_FILE_PATH, NULL);

	GObject *window = gtk_builder_get_object(builder, WINDOW_ID);
	gtk_window_set_application(GTK_WINDOW(window), app);

	GObject *button = gtk_builder_get_object(builder, "hello");



	g_object_unref(builder);
	
}

int main (int argc, char **argv)
{
#ifdef GTK_SRCDIR
	g_chdir (GTK_SRCDIR);
#endif
	GtkApplication *app = gtk_application_new ("ru.lunaro.paint-piet", 0);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

	int status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
