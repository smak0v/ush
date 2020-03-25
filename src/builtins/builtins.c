#include "ush.h"

int mx_ush_cd(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arguments = mx_store_files(args);
    char *illegal_option = 0;
    int status = 0;
    char *destination = NULL;

    if (flags && *flags && (illegal_option = mx_flags_validation(flags, cd)))
        return mx_cd_invalid_option(illegal_option);

    if (!arguments)
        destination = mx_getenv(ush->hidden, "HOME");
    else if (!mx_strcmp(*arguments, "-"))
        destination = mx_getenv(ush->hidden, "OLDPWD");
    else
        destination = *arguments;

    status = mx_cd(ush, flags, destination);

    mx_del_strarr(&flags);
    mx_del_strarr(&arguments);
    return status;
}

int mx_ush_pwd(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char *path = NULL;
    char *option = 0;

    if (flags && *flags && (option = mx_flags_validation(flags, pwd))) {
        mx_print_error_endl("to do: pwd error handling");
        return 1;
    }

    if (flags && *flags && flags[mx_strarr_len(flags) - 1][0] == 'P')
        path = mx_get_pwd();
    else
        path = mx_getenv(ush->hidden, "PWD");

    mx_printstr_endl(path);
    mx_strdel(&path);
    return 0;
}

int mx_ush_echo(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arguments = mx_store_files(args);

    // if (flags && (illegal_option = mx_flags_validation(flags, echo)) != 0) {
    //     mx_print_error_endl("to do: echo error handling");
    //     //mx_env_illegal_option(illegal_option);
    //     return 1;
    // }
    mx_print_strarr(arguments, " ");
    mx_del_strarr(&flags);
    mx_del_strarr(&arguments);
    return 0;
}


int mx_ush_which(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arguments = mx_store_files(args);
    char **output = NULL;
    char *illegal_option = NULL;
    int status = 0;

    if (flags && (illegal_option = mx_flags_validation(flags, which)))
        mx_which_invalid_option(illegal_option);
    else if (arguments) {
        output = mx_which(ush, flags, arguments, &status);
        if (!mx_check_flag(flags, 's'))
            mx_print_strarr(output, "\n");
        mx_del_strarr(&output);
    }
    else
        mx_which_usage_error(&status);

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
