#include <gtk/gtk.h>

static void	activate(GtkApplication *app, gpointer data)
{
	GtkWidget	*window;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Forgemancer");
	gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
	gtk_window_present(GTK_WINDOW(window));
}

int	main(int ac, char **av)
{
	GtkApplication	*app;
	int				status;

	app = gtk_application_new("fr.tsuunen.forgemancer", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), ac, av);
	g_object_unref(app);

	return (status);
}
