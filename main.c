// #include "gio/gio.h"
// #include "glib.h"
// #include "glib-object.h"
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

static void app_main(GtkApplication *app, gpointer user_data)
{ 
	return;
}

static void window_main(GtkWidget *window, gpointer user_data)
{ 
	return;
}

int main(int argc, char *argv[])
{
	GtkApplication *app;
	int status;

	app = gtk_application_new("org.application.me", G_APPLICATION_DEFAULT_FLAGS);
	// gtk_init();
	GtkWidget *window;
	window = gtk_window_new();
	gtk_widget_set_visible(window, true);

	g_signal_connect(app, "activate", G_CALLBACK(app_main), NULL);

	status = g_application_run(G_APPLICATION(app), argc, argv);

	return status;
}

