#include "ush.h"

static void print_line(t_input *in) {
    mx_shuffle_text(in);
    mx_printstr(in->line + in->cur_x);
    ++(in->cur_x);
    ++(in->win_x);
    mx_update_cursor(in);
}

static void edit_line(t_input *in) {
    if (in->key == MX_LEFT)
        mx_arrow_left(in);
    else if (in->key == MX_RIGHT)
        mx_arrow_right(in);
    else if (in->key == MX_BACKSPACE)
        mx_backspace(in);
}

static void read_input(t_ush *ush) {
    mx_init_terminal_data();
    ush->in->winsize = tgetnum("co");
    ush->in->key = 0;
    read(0, &ush->in->key, 4);
    if ((ush->in->key >= 32 && ush->in->key < 127)) {
        print_line(ush->in);
    }
    if (ush->in->key == MX_CTRL_C) {
        mx_printstr("\nu$h> ");
        mx_init_line(ush);
    }
    if (ush->in->key == MX_UP && ush->history)
        mx_arrow_up(ush);
    if (ush->in->key == MX_DOWN && ush->history)
        mx_arrow_down(ush);
}

char *mx_get_line(t_ush *ush) {
    mx_init_line(ush);
    mx_enable_input_mode(ush);
    while (ush->in->key != MX_ENTER) {
        read_input(ush);
        edit_line(ush->in);
    }
    mx_disable_input_mode(ush);
    mx_printstr("\n");
    if (ush->in->line[0])
        mx_add_cmd(&(ush->history), mx_create_hist_node(ush->in->line));
    ush->current = ush->history;
    return ush->in->line;
}
