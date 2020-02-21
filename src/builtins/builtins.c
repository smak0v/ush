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

int mx_ush_env(char **args, t_ush *ush) {
    t_env *setup = mx_parse_env(args);
    int status = 0;

    if (setup->error) {
        mx_env_illegal_option(setup->error);
        return 1;
    }
    if (setup->P && !mx_strcmp("No ArGuMeNt", setup->P)) {
        printf("test\n");
        mx_option_requires_an_argument('P');
        printf("test\n");
        return 1;
    }
    if (setup->u && !mx_strcmp("No ArGuMeNt", setup->u)) {
        mx_option_requires_an_argument('u');
        return 1;
    }
    // status = mx_env(flags, arguments);

    return status;
}

int mx_ush_echo(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arguments = mx_store_files(args);
    char illegal_option = 0;

    if (*flags && (illegal_option = mx_flags_validation(flags, echo)) != 0) {
        mx_print_error_endl("to do: echo error handling");
        //mx_env_illegal_option(illegal_option);
        return 1;
    }
    mx_print_strarr(arguments, " ");
    return 0;
}

int mx_ush_exit(char **args, t_ush *ush) {
    return 0;
}

