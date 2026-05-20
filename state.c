#include "state.h"
#include "calc.h"

#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct shake_widget_data
{
    GtkWidget *widget;
    int original_margin_start;
    int original_margin_end;
    int step;
};

static int apply_pending_operation(struct entry_calculator *state);
static void update_display(struct entry_calculator *state);

static void play_sound(void);
static int is_result_67(double value);
static void check_result_event(struct entry_calculator *state);
static void on_result_67(struct entry_calculator *state);

static void shake_widget(GtkWidget *widget);
static gboolean shake_widget_step(gpointer data);

struct entry_calculator init_calculator(GtkWidget *display)
{
    struct entry_calculator state;

    state.val_on_screen = 0.0;
    state.operande = 0.0;
    state.operation = '\0';
    state.waiting_second = 0;
    state.display = display;

    return state;
}

void on_digit_clicked(GtkWidget *widget, gpointer data)
{
    struct entry_calculator *state = (struct entry_calculator *)data;
    const char *label = gtk_button_get_label(GTK_BUTTON(widget));
    int digit = label[0] - '0';

    if (state->waiting_second == 0)
    {
        state->val_on_screen = state->val_on_screen * 10 + digit;
    }
    else
    {
        state->val_on_screen = digit;
        state->waiting_second = 0;
    }

    update_display(state);
}

void on_operator_clicked(GtkWidget *widget, gpointer data)
{
    struct entry_calculator *state = (struct entry_calculator *)data;
    char new_operation = gtk_button_get_label(GTK_BUTTON(widget))[0];

    if (state->operation != '\0' && state->waiting_second == 0)
    {
        if (apply_pending_operation(state))
            check_result_event(state);
    }

    state->operande = state->val_on_screen;
    state->operation = new_operation;
    state->waiting_second = 1;

    update_display(state);
}

void on_unary_clicked(GtkWidget *widget, gpointer data)
{
    struct entry_calculator *state = (struct entry_calculator *)data;
    const char *label = gtk_button_get_label(GTK_BUTTON(widget));

    if (strcmp(label, "√") == 0)
    {
        state->val_on_screen = squareroot(state->val_on_screen);
        check_result_event(state);
    }
    else if (strcmp(label, "1/x") == 0)
    {
        state->val_on_screen = inverse(state->val_on_screen);
        check_result_event(state);
    }

    state->waiting_second = 1;
    update_display(state);
}

void on_equal_clicked(GtkWidget *widget, gpointer data)
{
    (void)widget;

    struct entry_calculator *state = (struct entry_calculator *)data;

    if (state->operation == '\0')
        return;

    if (apply_pending_operation(state))
        check_result_event(state);

    state->operation = '\0';
    state->waiting_second = 1;

    update_display(state);
}

void on_ce_clicked(GtkWidget *widget, gpointer data)
{
    (void)widget;

    struct entry_calculator *state = (struct entry_calculator *)data;

    state->val_on_screen = 0.0;
    state->operande = 0.0;
    state->operation = '\0';
    state->waiting_second = 0;

    gtk_entry_set_text(GTK_ENTRY(state->display), "0");
}

void on_backspace_clicked(GtkWidget *widget, gpointer data)
{
    (void)widget;

    struct entry_calculator *state = (struct entry_calculator *)data;

    if (state->waiting_second == 1)
        return;

    const char *text = gtk_entry_get_text(GTK_ENTRY(state->display));

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%s", text);

    size_t length = strlen(buffer);

    if (length <= 1)
    {
        state->val_on_screen = 0.0;
        gtk_entry_set_text(GTK_ENTRY(state->display), "0");
        return;
    }

    buffer[length - 1] = '\0';

    if (strcmp(buffer, "-") == 0)
    {
        state->val_on_screen = 0.0;
        gtk_entry_set_text(GTK_ENTRY(state->display), "0");
        return;
    }

    state->val_on_screen = strtod(buffer, NULL);
    gtk_entry_set_text(GTK_ENTRY(state->display), buffer);
}

static int apply_pending_operation(struct entry_calculator *state)
{
    if (state->operation == '\0')
        return 0;

    switch (state->operation)
    {
    case '+':
        state->val_on_screen = add(state->operande, state->val_on_screen);
        break;

    case 'X':
        state->val_on_screen = multiply(state->operande, state->val_on_screen);
        break;

    case '-':
        state->val_on_screen = subtract(state->operande, state->val_on_screen);
        break;

    case '/':
        state->val_on_screen = divide(state->operande, state->val_on_screen);
        break;

    case '%':
        state->val_on_screen = modulo(state->operande, state->val_on_screen);
        break;

    case '^':
        state->val_on_screen = power(state->operande, state->val_on_screen);
        break;

    default:
        return 0;
    }

    return 1;
}

static void update_display(struct entry_calculator *state)
{
    char buffer[64];

    snprintf(buffer, sizeof(buffer), "%.10g", state->val_on_screen);
    gtk_entry_set_text(GTK_ENTRY(state->display), buffer);
}

static void play_sound(void)
{
    g_spawn_command_line_async("paplay 67.wav", NULL);
}

static int is_result_67(double value)
{
    return fabs(value - 67.0) < 0.000001;
}

static void check_result_event(struct entry_calculator *state)
{
    if (is_result_67(state->val_on_screen))
        on_result_67(state);
}

static void on_result_67(struct entry_calculator *state)
{
    GtkWidget *toplevel;
    GtkWidget *child;

    play_sound();

    toplevel = gtk_widget_get_toplevel(state->display);

    if (!GTK_IS_WINDOW(toplevel))
        return;

    child = gtk_bin_get_child(GTK_BIN(toplevel));

    if (child != NULL)
        shake_widget(child);
}

static void shake_widget(GtkWidget *widget)
{
    struct shake_widget_data *shake = g_malloc(sizeof(struct shake_widget_data));

    shake->widget = widget;
    shake->original_margin_start = gtk_widget_get_margin_start(widget);
    shake->original_margin_end = gtk_widget_get_margin_end(widget);
    shake->step = 0;

    g_timeout_add(25, shake_widget_step, shake);
}

static gboolean shake_widget_step(gpointer data)
{
    struct shake_widget_data *shake = (struct shake_widget_data *)data;

    if (shake->step % 2 == 0)
    {
        gtk_widget_set_margin_start(
            shake->widget,
            shake->original_margin_start + 20);

        gtk_widget_set_margin_end(
            shake->widget,
            shake->original_margin_end);
    }
    else
    {
        gtk_widget_set_margin_start(
            shake->widget,
            shake->original_margin_start);

        gtk_widget_set_margin_end(
            shake->widget,
            shake->original_margin_end + 20);
    }

    shake->step++;

    if (shake->step >= 20)
    {
        gtk_widget_set_margin_start(
            shake->widget,
            shake->original_margin_start);

        gtk_widget_set_margin_end(
            shake->widget,
            shake->original_margin_end);

        g_free(shake);
        return G_SOURCE_REMOVE;
    }

    return G_SOURCE_CONTINUE;
}