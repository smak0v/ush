#include "ush.h"

int mx_ush_history(char **args, t_ush *ush) {
    t_hist *hist = ush->history;
    char *intstr = NULL;

    args += 1;
    while (hist->next) {
        hist = hist->next;
    }

    for (int i = 1; hist; i++) {
        intstr = mx_itoa(i);
        printf("   %s  %s\n", intstr, hist->cmd);
        mx_strdel(&intstr);
        hist = hist->prev;
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

int mx_ush_true(char **args, t_ush *ush) {
    ush += 1;
    args += 1;

    return 0;
}

int mx_ush_false(char **args, t_ush *ush) {
    ush += 1;
    args += 1;

    return 1;
}
