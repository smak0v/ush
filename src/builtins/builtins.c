#include "ush.h"

extern char **environ;

int mx_ush_cd(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arguments = mx_store_files(args);
    //int status = mx_cd(flags, arguments);

    mx_print_strarr(environ, "\n");
    ush++;
    // int status = chdir(args[1]);

    // ush++; // Remove
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

    args++; // Remove
    ush++; // Remove
    getcwd(path, (size_t)size);
    mx_printstr_endl(path);
    mx_strdel(&path);
    return 1;
}

int mx_ush_env(char **args, t_ush *ush) {
    ush++; // Remove
    mx_print_strarr(args, "\n");
    return 1;
}

int mx_ush_echo(char **args, t_ush *ush) {
    char **tmp = args + 1;

    ush++; // Remove
    mx_print_strarr(tmp, " ");
    return 1;
}

int mx_ush_exit(char **args, t_ush *ush) {
    args++; // Remove
    ush++; // Remove
    return 0;
}

