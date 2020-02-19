#include "ush.h"

int mx_ush_cd(char **args, t_ush *ush) {
    int status = chdir(args[1]);

    ush++; // Remove
    if (status < 0) {
        mx_print_error("cd: ");
        mx_print_error(strerror(errno));
        mx_print_error(": ");
        mx_print_error_endl(args[1]);
        status = 1;
    }
    return status;
}

int mx_ush_pwd(char **args, t_ush *ush) {
    long size = pathconf(".", _PC_PATH_MAX);
    char *path = mx_strnew(size);

    args++; // Remove
    ush++; // Remove
    getcwd(path, (size_t)size);
    mx_printstr_endl(path);
    mx_strdel(&path);
    return 0;
}

int mx_ush_env(char **args, t_ush *ush) {
    ush++; // Remove
    mx_print_strarr(args, "\n");
    return 0;
}

int mx_ush_echo(char **args, t_ush *ush) {
    char **tmp = args + 1;

    ush++; // Remove
    mx_print_strarr(tmp, " ");
    return 0;
}

int mx_ush_exit(char **args, t_ush *ush) {
    args++; // Remove
    ush++; // Remove
    return 0;
}
