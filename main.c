#define G_APPLICATION_DEFAULT_FLAGS 0
#include <gtk/gtk.h>
#include <stdbool.h>
#include <stdio.h>
/* more stuff here */

static gboolean on_drop (GtkDropTarget *target){
	return TRUE;
}

static void app_main(GtkApplication *app, gpointer user_data)
{ 
	GtkWidget *window;
	window = gtk_application_window_new (app);
	
	gtk_window_set_title (GTK_WINDOW (window), "test");
	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
	gtk_window_present(GTK_WINDOW(window));

	GtkWidget *drag_and_drop;
	gtk_drop_target_new(G_TYPE_INVALID, GDK_ACTION_COPY);
	
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
	// GtkWidget *window;
	// window = gtk_window_new();
	// gtk_widget_set_visible(window, true);

	// gtk_application_add_window(app, window);

	g_signal_connect(app, "activate", G_CALLBACK(app_main), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);

	return status;
}

