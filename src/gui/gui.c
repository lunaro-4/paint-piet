#include "glib/gprintf.h"
#include <gtk/gtk.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define UI_FILE_PATH "src/gui/paint-piet.ui"
#define WINDOW_ID "main_window"

void handle_size_restrictions (GtkWidget *widget, gpointer data)
{
	int current_position = gtk_paned_get_position(GTK_PANED(widget));
	GtkWidget *start_child = gtk_paned_get_start_child(GTK_PANED(widget));
	int minimum, minimum_baseline;
	gtk_widget_measure(start_child, GTK_ORIENTATION_HORIZONTAL, -1, &minimum, NULL, &minimum_baseline, NULL);

	const char *name = gtk_widget_get_name(start_child);
	g_printf("%s", name);
	if (minimum_baseline > -1 && current_position < minimum_baseline)
	{
		gtk_paned_set_position(GTK_PANED(widget), minimum_baseline);
	}
}

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
