#include "ush.h"

int mx_no_job_control_error(void) {
    mx_print_error("ush: fg: no job control\n");
    return MX_FAILURE;
}

void mx_no_such_job_error(char *name) {
    mx_print_error("ush: fg: ");
    mx_print_error(name);
    mx_print_error(": no such job\n");
}

void mx_invalid_option_error(char *name) {
    char *tmp = mx_strndup(&name[1], 1);

    mx_print_error("ush: fg: -");
    mx_print_error(tmp);
    mx_strdel(&tmp);
    mx_print_error(": invalid option\n");
    mx_print_error("fg: usage: fg [job_spec]\n");
}

void mx_ambiguous_job_spec_error(char *name) {
    char *tmp = name;

    while (tmp && *tmp) {
        if (*tmp == '%') {
            ++tmp;
            continue;
        }
        else
            break;
    }
    mx_print_error("ush: fg: ");
    mx_print_error(tmp);
    mx_print_error(": ambiguous job spec\n");
}
