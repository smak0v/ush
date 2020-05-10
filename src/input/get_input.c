#include "ush.h"

void mx_print_line(t_input *in) {
    mx_shuffle_text(in);
    mx_printstr(in->line + in->cur_x);
    ++(in->cur_x);
    ++(in->win_x);
    mx_update_cursor(in);
}

void mx_ctrl_d(t_ush *ush) {
    if (ush->in->line[0]) {
        tputs(tgetstr("dc", NULL), 1, mx_printnbr);
        for (size_t i = ush->in->cur_x; i <= strlen(ush->in->line); i++)
            ush->in->line[i] = ush->in->line[i + 1];
        tputs(tgetstr("cd", NULL), 1, mx_printnbr);
        mx_printstr(ush->in->line + ush->in->cur_x);
        mx_update_cursor(ush->in);
    }
    else {
        mx_printstr("\n");
        exit(ush->exit_code > 0);
    }
}

static void read_input(t_ush *ush) {
    mx_init_terminal_data();
    ush->in->winsize = tgetnum("co");
    ush->in->key = 0;
    read(0, &ush->in->key, 4);
    if ((ush->in->key >= 32 && ush->in->key < 127))
        mx_print_line(ush->in);
    ush->in->key == MX_LEFT ? mx_arrow_left(ush->in) : (void)0;
    ush->in->key == MX_RIGHT ? mx_arrow_right(ush->in) : (void)0;
    ush->in->key == MX_BACKSPACE ? mx_backspace(ush->in) : (void)0;
    ush->in->key == MX_UP && ush->history ? mx_arrow_up(ush) : (void)0;
    ush->in->key == MX_DOWN && ush->history ? mx_arrow_down(ush) : (void)0;
    if (ush->in->key == MX_CTRL_C) {
        mx_printchar('\n');
        mx_print_prompt(ush);
        mx_init_line(ush);
    }
    else if (ush->in->key == MX_CTRL_D)
        mx_ctrl_d(ush);
    else if (ush->in->key == MX_ALT_1)
        mx_change_prompt(ush);
}

char *mx_get_line(t_ush *ush) {
    mx_init_line(ush);
    mx_enable_input_mode(ush);
    while (ush->in->key != MX_ENTER)
        read_input(ush);
    mx_disable_input_mode(ush);
    mx_printstr("\n");
    if (ush->in->line[0])
        mx_add_cmd(&(ush->history), mx_create_hist_node(ush->in->line));
    ush->current = ush->history;
    ush->in->chars_after_newline = 0;
    return ush->in->line;
}
