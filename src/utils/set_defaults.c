#include "ush.h"

static char **set_local(char **arr, int *not_found) {
    if (!not_found[PATH]) {
        char *path = MX_DEFAULT_PATH;

        arr = mx_add_var(arr, path);
    }
    if (!not_found[TERM]) {
        char *term = "TERM=xterm-256color";

        arr = mx_add_var(arr, term);
    }
    if (!not_found[HOME])
        arr = mx_process_home(arr);
    return arr;
}

static void set_pwd(t_ush *ush) {
    char *pwd = mx_build_pwd_str();
    char **key_value = mx_split_key_value(pwd);

    ush->env = mx_add_var(ush->env, pwd);
    ush->export = mx_add_var(ush->export, pwd);
    ush->local_variables = mx_add_var(ush->local_variables, pwd);
    setenv(key_value[0], key_value[1], 1);

    mx_strdel(&pwd);
}

static void init_hidden(t_ush *ush) {
    char *pwd = mx_strjoin("PWD=", getenv("PWD"));

    ush->hidden = mx_add_var(ush->hidden, "OLDPWD");
    ush->hidden = mx_add_var(ush->hidden, pwd);
    ush->hidden = mx_add_var(ush->hidden, "?=0");
    ush->hidden = mx_process_home(ush->hidden);

    mx_strdel(&pwd);
}

char **mx_add_var(char **export, char *keyword) {
    char **tmp = NULL;
    char *var_array[] = {keyword, NULL};

    tmp = export;
    export = mx_strarr_join(export, var_array);
    mx_del_strarr(&tmp);

    return export;
}

void mx_set_default(t_ush *ush, int *not_found) {
    if (!not_found[OLDPWD]) {
        ush->export = mx_add_var(ush->export, "OLDPWD");
        ush->local_variables = mx_add_var(ush->local_variables, "OLDPWD");
    }
    if (!not_found[PWD])
        set_pwd(ush);
    if (!not_found[SHLVL]) {
        ush->export = mx_add_var(ush->export, "SHLVL=1");
        ush->env = mx_add_var(ush->env, "SHLVL=1");
        setenv("SHLVL", "1", 1);
    }
    if (!not_found[PATH] || !not_found[TERM] || !not_found[HOME])
        ush->local_variables = set_local(ush->local_variables, not_found);

    init_hidden(ush);
}
