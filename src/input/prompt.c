#include "ush.h"

void mx_init_prompt(t_ush *ush) {
    ush->in->prompt = strdup("u$h> ");
    ush->in->prompt_length = strlen(ush->in->prompt);
}

void mx_update_prompt(t_ush *ush) {
    char *pwd = NULL;

    if (strcmp(ush->in->prompt, "u$h> ") == 0)
        return;
    mx_strdel(&ush->in->prompt);
    pwd = mx_getenv(ush->hidden, "PWD");
    ush->in->prompt = mx_strnew(strlen(pwd) + 2);
    strcat(ush->in->prompt, pwd);
    strcat(ush->in->prompt, "> ");
    ush->in->prompt_length = strlen(ush->in->prompt);
    mx_strdel(&pwd);
}

static void reprint_line(t_ush *ush) {
    char *line = strdup(ush->in->line);

    tputs(tgetstr("cr", NULL), 1, mx_printnbr);
    tputs(tgetstr("cd", NULL), 1, mx_printnbr);
    mx_init_line(ush);
    strcat(ush->in->line, line);
    mx_strdel(&line);
    mx_print_prompt(ush);
    mx_printstr(ush->in->line);
    ush->in->cur_x = strlen(ush->in->line);
    ush->in->cur_y += (
        (ush->in->cur_x + ush->in->prompt_length - 1) / ush->in->winsize);
    if ((ush->in->cur_x + ush->in->prompt_length) > ush->in->winsize)
        ush->in->win_x = (ush->in->cur_x
                          + ush->in->prompt_length
                          - (ush->in->winsize * (ush->in->cur_y - 1)));
    else
        ush->in->win_x = (ush->in->cur_x + ush->in->prompt_length);
    mx_update_cursor(ush->in);
}

void mx_change_prompt(t_ush *ush) {
    char *pwd = NULL;

    if (strcmp(ush->in->prompt, "u$h> ") == 0) {
        mx_strdel(&ush->in->prompt);
        pwd = mx_getenv(ush->hidden, "PWD");
        ush->in->prompt = mx_strnew(strlen(pwd) + 2);
        strcat(ush->in->prompt, pwd);
        strcat(ush->in->prompt, "> ");
        mx_strdel(&pwd);
    } else {
        mx_strdel(&ush->in->prompt);
        ush->in->prompt = strdup("u$h> ");
    }
    mx_cursor_to_promt(ush->in);
    ush->in->prompt_length = strlen(ush->in->prompt);
    reprint_line(ush);
}

void mx_print_prompt(t_ush *ush) {
    if (strcmp(ush->in->prompt, "u$h> ") == 0)
        mx_printstr(ush->in->prompt);
    else {
        mx_printstr("\033[36;1m");
        mx_printstr(ush->in->prompt);
        mx_printstr("\033[33;0m");
    }
}
