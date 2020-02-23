#include "ush.h"

static void command_not_found(char *cmd) {
    mx_print_error("ush: command not found: ");
    mx_print_error_endl(cmd);
}

static void no_such_file_or_directory(char *cmd) {
    char *command = mx_memrchr(cmd, '/', mx_strlen(cmd));

    command += 1;
    mx_print_error("env: ");
    mx_print_error(command);
    mx_print_error_endl(": No such file or directory");

}

void mx_choose_error(char **args, char **env) {
    if (!env)
        command_not_found(args[0]);
    else
        no_such_file_or_directory(args[0]);
}
