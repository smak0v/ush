#include "ush.h"

void mx_print_unset_error(char *flag) {
    mx_print_error("unset: bad option: -");
    mx_print_error_endl(flag);
}
