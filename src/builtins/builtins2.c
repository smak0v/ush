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

    return status;
}

int mx_ush_export(char **args, t_ush *ush) {
    char **arguments = mx_store_files(args);
    mx_print_strarr(arguments, " ");

    return 0;
}

int mx_ush_unset(char **args, t_ush *ush) {
    char **flags = mx_store_flags(args);
    char **arg = mx_store_files(args);

    if (flags) {
        mx_print_unset_error(flags[0]);
        mx_del_strarr(&flags);
        return 1;
    }
    for (int i = 0; i < mx_strarr_len(arg); i++) {
        unsetenv(arg[i]);
        ush->env = mx_popn_string_array(ush->env, arg[i], mx_strlen(arg[i]));
        ush->export = mx_popn_string_array(ush->export, arg[i], 
                                           mx_strlen(arg[i]));
        ush->local_variables = mx_popn_string_array(ush->local_variables,
                                                    arg[i], mx_strlen(arg[i]));
    }
    mx_del_strarr(&args);
    mx_del_strarr(&arg);
    return 0;
}

int mx_ush_local(char **args, t_ush *ush) {
    mx_del_strarr(&args);
    mx_print_strarr(ush->local_variables, "\n");
    return 0;
}
