#include <gtk/gtk.h>
#include "state.h"
#include <stdlib.h>
void destroy(GtkWidget *widget, gpointer data)
{
    g_application_quit(G_APPLICATION(data));
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;

    GtkWidget *button_0;
    GtkWidget *button_1;
    GtkWidget *button_2;
    GtkWidget *button_3;
    GtkWidget *button_4;
    GtkWidget *button_5;
    GtkWidget *button_6;
    GtkWidget *button_7;
    GtkWidget *button_8;
    GtkWidget *button_9;

    GtkWidget *mod_button;        // %
    GtkWidget *inverse_button;    // 1/x
    GtkWidget *power_button;      // ^
    GtkWidget *squareroot_button; // racine carré

    GtkWidget *add_button;      // +
    GtkWidget *multiply_button; // a*b
    GtkWidget *subtract_button; // a-b
    GtkWidget *divide_button;   // a/b

    GtkWidget *equal_button;   // =
    GtkWidget *clear_button;   // CE
    GtkWidget *decimal_button; // ,
    GtkWidget *cancel_button;  // RETOUR

    GtkWidget *grid;
    GtkWidget *display;

    // WINDOW
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 320, 500);

    display = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(display), "0");
    gtk_editable_set_editable(GTK_EDITABLE(display), FALSE);
    gtk_entry_set_alignment(GTK_ENTRY(display), 1.0);

    // ZONE BUTTONS

    button_0 = gtk_button_new_with_label("0");
    button_1 = gtk_button_new_with_label("1");
    button_2 = gtk_button_new_with_label("2");
    button_3 = gtk_button_new_with_label("3");
    button_4 = gtk_button_new_with_label("4");
    button_5 = gtk_button_new_with_label("5");
    button_6 = gtk_button_new_with_label("6");
    button_7 = gtk_button_new_with_label("7");
    button_8 = gtk_button_new_with_label("8");
    button_9 = gtk_button_new_with_label("9");

    mod_button = gtk_button_new_with_label("%");
    inverse_button = gtk_button_new_with_label("1/x");
    power_button = gtk_button_new_with_label("^");
    squareroot_button = gtk_button_new_with_label("√");

    add_button = gtk_button_new_with_label("+");
    multiply_button = gtk_button_new_with_label("X");
    subtract_button = gtk_button_new_with_label("-");
    divide_button = gtk_button_new_with_label("/");

    equal_button = gtk_button_new_with_label("=");
    clear_button = gtk_button_new_with_label("CE");
    decimal_button = gtk_button_new_with_label(",");
    cancel_button = gtk_button_new_with_label("⌫");

    // GRID
    grid = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    gtk_grid_attach(GTK_GRID(grid), display, 0, 0, 4, 1);

    //
    gtk_grid_attach(GTK_GRID(grid), clear_button, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), cancel_button, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), mod_button, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), divide_button, 3, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), inverse_button, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), power_button, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), squareroot_button, 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), multiply_button, 3, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), button_7, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_8, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_9, 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), subtract_button, 3, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), button_4, 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_5, 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_6, 2, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), add_button, 3, 4, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), button_1, 0, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_2, 1, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button_3, 2, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), equal_button, 3, 5, 1, 2);

    gtk_grid_attach(GTK_GRID(grid), button_0, 0, 6, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), decimal_button, 2, 6, 1, 1);

    struct entry_calculator *state = malloc(sizeof(struct entry_calculator));
    *state = init_calculator(display);

    g_signal_connect(button_0, "clicked", G_CALLBACK(on_digit_clicked), state);
    g_signal_connect(button_1, "clicked", G_CALLBACK(on_digit_clicked), state);
    g_signal_connect(button_2, "clicked", G_CALLBACK(on_digit_clicked), state);
    g_signal_connect(button_3, "clicked", G_CALLBACK(on_digit_clicked), state);
    g_signal_connect(button_4, "clicked", G_CALLBACK(on_digit_clicked), state);
    g_signal_connect(button_5, "clicked", G_CALLBACK(on_digit_clicked), state);
    g_signal_connect(button_6, "clicked", G_CALLBACK(on_digit_clicked), state);
    g_signal_connect(button_7, "clicked", G_CALLBACK(on_digit_clicked), state);
    g_signal_connect(button_8, "clicked", G_CALLBACK(on_digit_clicked), state);
    g_signal_connect(button_9, "clicked", G_CALLBACK(on_digit_clicked), state);

    g_signal_connect(add_button, "clicked", G_CALLBACK(on_operator_clicked), state);
    g_signal_connect(subtract_button, "clicked", G_CALLBACK(on_operator_clicked), state);
    g_signal_connect(multiply_button, "clicked", G_CALLBACK(on_operator_clicked), state);
    g_signal_connect(divide_button, "clicked", G_CALLBACK(on_operator_clicked), state);
    g_signal_connect(mod_button, "clicked", G_CALLBACK(on_operator_clicked), state);
    g_signal_connect(power_button, "clicked", G_CALLBACK(on_operator_clicked), state);

    g_signal_connect(squareroot_button, "clicked", G_CALLBACK(on_unary_clicked), state);
    g_signal_connect(inverse_button, "clicked", G_CALLBACK(on_unary_clicked), state);

    g_signal_connect(equal_button, "clicked", G_CALLBACK(on_equal_clicked), state);
    g_signal_connect(clear_button, "clicked", G_CALLBACK(on_ce_clicked), state);
    g_signal_connect(cancel_button, "clicked", G_CALLBACK(on_backspace_clicked), state);
    gtk_container_add(GTK_CONTAINER(window), grid);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("io.github.driftbyte.Calculator", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}