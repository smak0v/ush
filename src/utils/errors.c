#include "ush.h"

void mx_choose_error(char **args, char **env) {
    if (!env)
        mx_command_not_found_error(args[0]);
    else
        mx_no_such_file_or_directory(args[0]);
}

int mx_multiline_input_error(t_ush *ush) {
    mx_print_error("ush: multiline input not supported\n");

    ush->exit_code = 1;

    return MX_FAILURE;
}
