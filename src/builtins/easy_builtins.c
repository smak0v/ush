#include "ush.h"

int mx_ush_history(char **args, t_ush *ush) {
    t_hist *hist = ush->history;
    args += 1;

    while (hist->prev) {
        hist = hist->prev;
    }

    while (hist) {
        mx_printstr_endl(hist->cmd);
        hist = hist->next;
    }

    return 0;
}

int mx_ush_return(char **args, t_ush *ush) {
    int arg = 0;

    if (args[2]) {
        mx_print_error_endl("return: too many arguments");
        arg = 1;
    }
    else
        arg = atoi(*(args + 1));

    ush += 1;
    return arg;
}
