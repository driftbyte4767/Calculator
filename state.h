#ifndef STATE_H
#define STATE_H

#include <gtk/gtk.h>

struct entry_calculator
{
    double val_on_screen;
    double operande;
    char operation;
    int waiting_second;
    GtkWidget *display;
};

struct entry_calculator init_calculator(GtkWidget *display);
void on_digit_clicked(GtkWidget *widget, gpointer data);
void on_operator_clicked(GtkWidget *widget, gpointer data);
void on_ce_clicked(GtkWidget *widget, gpointer data);
void on_equal_clicked(GtkWidget *widget, gpointer data);
void on_unary_clicked(GtkWidget *widget, gpointer data);
void on_backspace_clicked(GtkWidget *widget, gpointer data);
static void play_sound(void);
static void on_result_67(struct entry_calculator *state);
static int is_result_67(double value);
static void check_result_event(struct entry_calculator *state);

#endif