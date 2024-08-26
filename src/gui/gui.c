
#include <gtk/gtk.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void print_hello (GtkWidget *widget, gpointer data)
{
	g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;	// window
	GtkWidget *button, *button2;	// button
	// GtkWidget *button_list;	// list_box
	GtkWidget *main_layout;	// HBox
	GtkWidget *left_column, *right_column;	// VBox


	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Hello");
	gtk_window_set_default_size (GTK_WINDOW (window), 800, 300);

	main_layout = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
	left_column = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);
	right_column = gtk_box_new(GTK_ORIENTATION_VERTICAL, 2);

	// button = gtk_button_new_with_label ("Hello World");
	// button2 = gtk_button_new_with_label ("Hello The Seckond");
	// gtk_list_box_append(GTK_LIST_BOX(button_list), button);
	// gtk_list_box_append(GTK_LIST_BOX(button_list), button2);
	// g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
	// g_signal_connect (button2, "clicked", G_CALLBACK (print_hello), NULL);
	
	gtk_window_set_child (GTK_WINDOW (window), button_list);

	gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new ("ru.lunaro.paint-piet", 0);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
