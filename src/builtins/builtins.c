#include "ush.h"

int mx_ush_cd(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arguments = mx_store_files(args);
    char illegal_option = 0;
    //int status = mx_cd(flags, arguments);

    if (*flags && (illegal_option = mx_flags_validation(flags, cd)) != 0) {
        mx_print_error_endl("to do: cd error handling");
        //mx_env_illegal_option(illegal_option);
        return 1;
    }

    // int status = chdir(args[1]);
    // if (status < 0) {
    //     mx_print_error("cd: ");
    //     mx_print_error(strerror(errno));
    //     mx_print_error(": ");
    //     mx_print_error_endl(args[1]);
    // }
    return 1;
}

int mx_ush_pwd(char **args, t_ush *ush) {
    long size = pathconf(".", _PC_PATH_MAX);
    char *path = mx_strnew(size);

    getcwd(path, (size_t)size);
    mx_printstr_endl(path);
    mx_strdel(&path);
    return 0;
}

int mx_ush_echo(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arguments = mx_store_files(args);
    char illegal_option = 0;

    // if (flags && (illegal_option = mx_flags_validation(flags, echo)) != 0) {
    //     mx_print_error_endl("to do: echo error handling");
    //     //mx_env_illegal_option(illegal_option);
    //     return 1;
    // }
    mx_print_strarr(arguments, " ");
    return 0;
}

int mx_ush_which(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arguments = mx_store_files(args);
    char *illegal_option = NULL;
    int status = 0;


    if (flags && (illegal_option = mx_flags_validation(flags, which))) {
        mx_which_invalid_option(illegal_option);
    }

    if (arguments) {
        mx_which(ush, flags, arguments, &status);
    }

    return status;
}

int mx_ush_exit(char **args, t_ush *ush) {
    ush->exit = 1;
    return 0;
}
