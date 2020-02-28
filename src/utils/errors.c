#include "ush.h"

void mx_choose_error(char **args, char **env) {
    if (!env)
        mx_command_not_found_error(args[0]);
    else
        mx_no_such_file_or_directory(args[0]);
}
