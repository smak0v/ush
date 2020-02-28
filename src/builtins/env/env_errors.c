#include "ush.h"

static void print_usage() {
    mx_print_error("\nusage: env [-i] [-P utilpath] [-u name]\n ");
    mx_print_error_endl("          [name=value ...] [utility [argument ...]]");
}

void mx_env_illegal_option(char illegal_option) {
    mx_print_error("env: illegal option -- ");
    write(2, &illegal_option, sizeof(char));
    print_usage();
}

void mx_option_requires_an_argument(char option) {
    fprintf(stderr, "env: option requires an argument -- %c", option);
    print_usage();
}
