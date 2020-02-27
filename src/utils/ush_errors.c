#include "ush.h"

void mx_proccess_start_error(char *process_name) {
    mx_print_error("ush: ");
    mx_print_error(process_name);
    mx_print_error(": error starting a new proccess\n");
}

void mx_command_not_found_error(char *command_name) {
    mx_print_error("ush: ");
    mx_print_error(command_name);
    mx_print_error(": command not found\n");
}
