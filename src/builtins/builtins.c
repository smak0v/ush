#include "ush.h"

int mx_ush_cd(char **args) {
    int status = chdir(args[1]);

    if (status < 0) {
        mx_print_error("cd: ");
        mx_print_error(strerror(errno));
        mx_print_error(": ");
        mx_print_error_endl(args[1]);
    }
    return 1;
}

int mx_ush_pwd() {
    long size = pathconf(".", _PC_PATH_MAX);
    char *path = mx_strnew(size);

    getcwd(path, (size_t)size);
    mx_printstr_endl(path);
    mx_strdel(&path);
    return 1;
}

int mx_ush_env(char **args) {
    mx_print_strarr(args, "\n");
    return 1;
}

int mx_ush_echo(char **args) {
    char **tmp = args + 1;

    mx_print_strarr(tmp, " ");
    return 1;
}

int mx_ush_exit() {
    return 0;
}
