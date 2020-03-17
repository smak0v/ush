#include "ush.h"

int mx_ush_cd(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arguments = mx_store_files(args);
    char *illegal_option = 0;
    int status = 0;

    if (flags && *flags && (illegal_option = mx_flags_validation(flags, cd))) {
        mx_print_error_endl("to do: cd error handling");
        //mx_env_illegal_option(illegal_option);
        return 1;
    }

    status = mx_cd(ush, flags, arguments);


    return status;
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

    if (flags && (illegal_option = mx_flags_validation(flags, which)))
        mx_which_invalid_option(illegal_option);
    if (arguments)
        mx_which(ush, flags, arguments, &status);
    else {
        mx_print_error_endl("usage: which [-as] program ...");
        status = 1;
    }
    mx_del_strarr(&flags);
    mx_del_strarr(&arguments);
    return status;
}

int mx_ush_exit(char **args, t_ush *ush) {
    char **arg = mx_store_files(args);;
    int code = 0;
    int exit = 0;

    if ((ush->suspended && !ush->delete_suspended) && (code = MX_FAILURE)) {
        ush->delete_suspended = true;
        mx_have_suspended_jobs_error();
    }
    else
        exit = 1;
    if (!arg)
        code = ush->exit_code > 0 ? 1 : 0;
    else
        code = mx_exit(arg, &exit);
    if (exit)
        ush->exit = &code;
    mx_del_strarr(&arg);
    return code;
}
