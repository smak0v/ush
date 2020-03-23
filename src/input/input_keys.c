#include "ush.h"

void mx_arrow_left(t_input *in) {
    if (in->cur_x != 0) {
        if (in->win_x == 0) {
            tputs(tgetstr("up", NULL), 1, mx_printnbr);
            while (in->win_x != in->winsize - 1) {
                tputs(tgetstr("nd", NULL), 1, mx_printnbr);
                ++(in->win_x);
            }
            --(in->cur_y);
        } else {
            tputs(tgetstr("le", NULL), 1, mx_printnbr);
            --(in->win_x);
        }
        --(in->cur_x);
    }
}

void mx_arrow_right(t_input *in) {
    if (in->key == MX_RIGHT && in->cur_x < strlen(in->line)) {
        if (in->win_x == in->winsize - 1) {
            tputs(tgetstr("do", NULL), 1, mx_printnbr);
            tputs(tgetstr("cr", NULL), 1, mx_printnbr);
            in->win_x = 0;
            ++(in->cur_y);
        } else {
            tputs(tgetstr("nd", NULL), 1, mx_printnbr);
            ++(in->win_x);
        }
        ++(in->cur_x);
    }
}

void mx_arrow_up(t_ush *ush) {
    while (ush->in->cur_y != 1) {
        tputs(tgetstr("up", NULL), 1, mx_printnbr);
        --(ush->in->cur_y);
    }
    while (ush->in->win_x != 5) {
        tputs(tgetstr("le", NULL), 1, mx_printnbr);
        --(ush->in->win_x);
    }
    tputs(tgetstr("cd", NULL), 1, mx_printnbr);
    mx_init_line(ush);
    mx_strcat(ush->in->line, ush->current->cmd);
    if (ush->current->next)
        ush->current = ush->current->next;
    mx_printstr(ush->in->line);
    ush->in->cur_x = strlen(ush->in->line);
    ush->in->cur_y += (strlen(ush->in->line) + 4) / ush->in->winsize;
    ush->in->win_x = (ush->in->cur_x > ush->in->winsize
        ? ((ush->in->cur_x + 5)) - (ush->in->winsize * ush->in->cur_y)
        : (ush->in->cur_x + 5));
    // printf("\n cur_x = %d\n win_x = %d\n cur_y = %d\n", ush->in->cur_x, ush->in->win_x, ush->in->cur_y);
}

void mx_arrow_down(t_ush *ush) {
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
    ush->in->win_x = (ush->in->cur_x > ush->in->winsize
                          ? (ush->in->cur_x + 5) - (ush->in->winsize * ush->in->cur_y)
                          : (ush->in->cur_x + 5));
}

void mx_backspace(t_input *in) {
    if (in->key == MX_BACKSPACE && in->cur_x != 0) {
        mx_arrow_left(in);
        tputs(tgetstr("dc", NULL), 1, mx_printnbr);
        mx_shuffle_text(in);
        tputs(tgetstr("cd", NULL), 1, mx_printnbr);
        mx_printstr(in->line + in->cur_x);
        mx_update_cursor(in);
    }
}
