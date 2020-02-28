#include "ush.h"

void mx_no_such_file_or_directory(char *cmd) {
    char *command = mx_memrchr(cmd, '/', mx_strlen(cmd));

    command += 1;
    mx_print_error("env: ");
    mx_print_error(command);
    mx_print_error_endl(": No such file or directory");
}

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
