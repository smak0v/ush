#include "ush.h"

void arrow_left(t_input *in) {
    if (in->cur_x != 0) {
        if (in->win_x == 1) {
            tputs(tgetstr("up", NULL), 1, mx_printnbr);
            while (in->win_x++ != in->winsize)
                tputs(tgetstr("nd", NULL), 1, mx_printnbr);
            --(in->cur_x);
        } else {
            tputs(tgetstr("le", NULL), 1, mx_printnbr);
            --(in->cur_x);
            --(in->win_x);
        }
    }
}

void arrow_right(t_input *in) {
    if (in->cur_x < strlen(in->line)) {
        tputs(tgetstr("nd", NULL), 1, mx_printnbr);
        ++(in->cur_x);
        ++(in->win_x);
    }
}

void arrow_up(t_ush *ush) {
    mx_memset(ush->in->line, 0, strlen(ush->in->line));
    mx_strcat(ush->in->line, ush->current->cmd);
    if (ush->current->next)
        ush->current = ush->current->next;
    while (ush->in->cur_y != 1) {
        tputs(tgetstr("up", NULL), 1, mx_printnbr);
        --(ush->in->cur_y);
    }
    while (ush->in->win_x != 5) {
        tputs(tgetstr("le", NULL), 1, mx_printnbr);
        --(ush->in->win_x);
    }
    tputs(tgetstr("cd", NULL), 1, mx_printnbr);
    mx_printstr(ush->in->line);
    ush->in->cur_x = strlen(ush->in->line);
    ush->in->win_x = (
        ush->in->cur_x > ush->in->winsize
            ? (ush->in->cur_x + 5) - (ush->in->winsize * ush->in->cur_y)
            : (ush->in->cur_x + 5));
}

void arrow_down(t_ush *ush) {
    mx_memset(ush->in->line, 0, strlen(ush->in->line));
    mx_strcat(ush->in->line, ush->current->cmd);
    if (ush->current->prev)
        ush->current = ush->current->prev;
    while (ush->in->cur_y != 1) {
        tputs(tgetstr("up", NULL), 1, mx_printnbr);
        --(ush->in->cur_y);
    }
    while (ush->in->win_x != 5) {
        tputs(tgetstr("le", NULL), 1, mx_printnbr);
        --(ush->in->win_x);
    }
    tputs(tgetstr("cd", NULL), 1, mx_printnbr);
    mx_printstr(ush->in->line);
    ush->in->cur_x = strlen(ush->in->line);
    ush->in->win_x = (
        ush->in->cur_x > ush->in->winsize
            ? (ush->in->cur_x + 5) - (ush->in->winsize * ush->in->cur_y)
            : (ush->in->cur_x + 5));
}

static void shuffle_text(t_input *in) {
    if (in->key == MX_BACKSPACE) {
        for (size_t i = in->cur_x; i <= strlen(in->line); i++)
            in->line[i] = in->line[i + 1];
    } else {
        for (size_t i = strlen(in->line); i > in->cur_x; i--)
            in->line[i] = in->line[i - 1];
        in->line[in->cur_x] = in->key;
    }
    in->line[strlen(in->line)] = 0;
}

void print_line(t_input *in) {
    shuffle_text(in);
    ++(in->cur_x);
    ++(in->win_x);
    tputs(tgetstr("im", NULL), 1, mx_printnbr);
    mx_printchar(in->key);
    tputs(tgetstr("ei", NULL), 1, mx_printnbr);
    // доделать перенос на новую строку, переписать всю эту дрочь красиво
}

static void edit_line(t_input *in) {
    if (in->key == MX_LEFT && in->cur_x != 0) {
        if (in->win_x == 1) {
            tputs(tgetstr("up", NULL), 1, mx_printnbr);
            while (in->win_x++ != in->winsize)
                tputs(tgetstr("nd", NULL), 1, mx_printnbr);
            --(in->cur_x);
        } else {
            tputs(tgetstr("le", NULL), 1, mx_printnbr);
            --(in->cur_x);
            --(in->win_x);
        }
    } else if (in->key == MX_RIGHT && in->cur_x < strlen(in->line)) {
        tputs(tgetstr("nd", NULL), 1, mx_printnbr);
        ++(in->cur_x);
        ++(in->win_x);
    } else if (in->key == MX_BACKSPACE && in->cur_x != 0) {
        tputs(tgetstr("le", NULL), 1, mx_printnbr);
        tputs(tgetstr("dc", NULL), 1, mx_printnbr);
        --(in->cur_x);
        --(in->win_x);
        shuffle_text(in);
    }
}

static void read_input(t_ush *ush) {
    mx_init_terminal_data();
    ush->in->winsize = tgetnum("co");
    ush->in->key = 0;
    read(0, &ush->in->key, 4);
    if ((ush->in->key >= 32 && ush->in->key < 127)) {
        print_line(ush->in);
    }
    if (ush->in->key == MX_UP)
        ush->history ? arrow_up(ush) : (void)0;
    if (ush->in->key == MX_DOWN)
        ush->history ? arrow_down(ush) : (void)0;
}

char *mx_get_line(t_ush *ush) {
    ush->in->line = mx_memalloc(1024);
    ush->in->key = 0;
    ush->in->cur_x = 0;
    ush->in->win_x = 5;
    ush->in->cur_y = 1;
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
