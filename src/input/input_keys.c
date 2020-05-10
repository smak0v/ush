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
        }
        else {
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
        }
        else {
            tputs(tgetstr("nd", NULL), 1, mx_printnbr);
            ++(in->win_x);
        }
        ++(in->cur_x);
    }
}

void mx_arrow_up(t_ush *ush) {
    mx_cursor_to_promt(ush->in);
    tputs(tgetstr("cd", NULL), 1, mx_printnbr);
    mx_init_line(ush);
    mx_strcat(ush->in->line, ush->current->cmd);
    if (ush->current->next) {
        ush->current->next->prev = ush->current;
        ush->current = ush->current->next;
    }
    mx_printstr(ush->in->line);
    ush->in->cur_x = strlen(ush->in->line);
    ush->in->cur_y += (
        (ush->in->cur_x + ush->in->prompt_length - 1) / ush->in->winsize);
    ush->in->win_x = ush->in->cur_x + ush->in->prompt_length
                     + ush->in->chars_after_newline;
    if ((ush->in->cur_x + ush->in->prompt_length) > ush->in->winsize)
        ush->in->win_x -= ush->in->winsize * (ush->in->cur_y - 1);
    mx_update_cursor(ush->in);
}

void mx_arrow_down(t_ush *ush) {
    mx_cursor_to_promt(ush->in);
    tputs(tgetstr("cd", NULL), 1, mx_printnbr);
    mx_init_line(ush);
    if (ush->current->prev) {
        ush->current->prev->next = ush->current;
        ush->current = ush->current->prev;
        mx_strcat(ush->in->line, ush->current->cmd);
        mx_printstr(ush->in->line);
        ush->in->cur_x = strlen(ush->in->line);
        ush->in->cur_y += (
            (ush->in->cur_x + ush->in->prompt_length - 1) / ush->in->winsize);
        ush->in->win_x = ush->in->cur_x + ush->in->prompt_length
                     + ush->in->chars_after_newline;
        if ((ush->in->cur_x + ush->in->prompt_length) > ush->in->winsize)
            ush->in->win_x -= ush->in->winsize * (ush->in->cur_y - 1);
        mx_update_cursor(ush->in);
    }
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
