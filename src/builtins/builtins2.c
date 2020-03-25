#include "ush.h"

int mx_ush_env(char **args, t_ush *ush) {
    t_env *setup = mx_parse_env(args);
    int status = 0;

    if (setup->error) {
        mx_env_illegal_option(setup->error);
        return 1;
    }
    if (setup->P && !mx_strcmp("No ArG", setup->P)) {
        mx_option_requires_an_argument('P');
        return 1;
    }
    if (setup->u && !mx_strcmp("No ArG", setup->u)) {
        mx_option_requires_an_argument('u');
        return 1;
    }

    status = mx_env(setup, ush);
    mx_env_janitor(&setup);
    return status;
}

int mx_ush_export(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arguments = mx_store_files(args);
    int status = 0;

    if (flags) {
        mx_export_invalid_option(*flags);
        mx_del_strarr(&flags);
        return 1;
    }
    if (arguments) {
        mx_export(arguments, ush, &status);
        mx_del_strarr(&arguments);
    }
    else
        mx_print_strarr(ush->export, "\n");

    return status;
}

int mx_ush_unset(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arg = mx_store_files(args);
    int status = 0;

    if (flags) {
        mx_unset_invalid_option(*flags);
        mx_del_strarr(&flags);
        return 1;
    }
    mx_unset(ush, arg, &status);
    return status;
}

int mx_ush_local(char **args, t_ush *ush) {
    args += 1;
    mx_print_strarr(ush->local_variables, "\n");
    return 0;
}
