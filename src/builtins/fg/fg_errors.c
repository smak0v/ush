#include "ush.h"

void mx_no_such_job_error(char *name) {
    mx_print_error("ush: fg: ");
    mx_print_error(name);
    mx_print_error(": no such job\n");
}
