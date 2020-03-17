#include "ush.h"

void mx_no_such_job_error(char *name) {
    mx_print_error("ush: fg: ");
    mx_print_error(name);
    mx_print_error(": no such job\n");
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
