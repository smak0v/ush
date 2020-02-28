#include "ush.h"

void mx_unset_invalid_option(char *option) {
    mx_print_error("ush: unset: -");
    mx_print_error(option);
    mx_print_error_endl(": invalid option");
    mx_print_error_endl("unset: usage: unset [name ...]");
}

void mx_export_invalid_option(char *option) {
    mx_print_error("ush: export: -");
    mx_print_error(option);
    mx_print_error_endl(": invalid option");
    mx_print_error_endl("export: usage: export [name[=value] ...]");
}

void mx_invalid_identifier(char *cmd, char *identifier) {
    mx_print_error("ush: ");
    mx_print_error(cmd);
    mx_print_error(": `");
    mx_print_error(identifier);
    mx_print_error_endl("': not a valid identifier");
}
