#include "ush.h"

void mx_env_illegal_option(char illegal_option) {
    mx_print_error("env: illegal option -- ");
    write(2, &illegal_option, sizeof(char));
    mx_print_error_endl("\nusage: env [-i] [-P utilpath] [-u name]\n           [name=value ...] [utility [argument ...]]");
}
