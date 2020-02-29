#include "ush.h"

static char **set_local(char **arr, int *not_found) {
    char **tmp = NULL;

    if (!not_found[PATH]) {
        char *path[] = {"PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:", NULL};

        tmp = arr;
        arr = mx_strarr_join(arr, path);
        mx_del_strarr(&tmp);
    }
    if (!not_found[TERM]) {
        char *term[] = {"TERM=xterm-256color", NULL};

        tmp = arr;
        arr = mx_strarr_join(arr, term);
        mx_del_strarr(&tmp);
    }
    if (!not_found[HOME])
        arr = mx_process_home(arr);
    return arr;
}

char **add_var(char **export, char *keyword) {
    char **tmp = NULL;
    char *oldpwd[] = {keyword, NULL};

    tmp = export;
    export = mx_strarr_join(export, oldpwd);
    mx_del_strarr(&tmp);

    return export;
}

static void set_pwd(t_ush *ush) {
    char **tmp = NULL;
    long size = pathconf(".", _PC_PATH_MAX);
    char *path = mx_strnew(size);
    char **pwd = NULL;
    char *tmp_str = NULL;

    getcwd(path, (size_t)size);
    tmp_str = mx_strjoin("PWD=", path);
    pwd = calloc(2, sizeof(char *));
    pwd[0] = mx_strdup(tmp_str);
    mx_strdel(&tmp_str);
    mx_strdel(&path);
    tmp = ush->env;
    ush->env = mx_strarr_join(ush->env, pwd);
    mx_del_strarr(&tmp);
    tmp = ush->export;
    ush->export = mx_strarr_join(ush->export, pwd);
    mx_del_strarr(&tmp);
    tmp = ush->local_variables;
    ush->local_variables = mx_strarr_join(ush->local_variables, pwd);
    mx_del_strarr(&tmp);
}

void mx_set_default(t_ush *ush, int *not_found) {

    if (!not_found[OLDPWD]) {
        ush->export = add_var(ush->export, "OLDPWD");
        ush->local_variables = add_var(ush->local_variables, "OLDPWD");
    }
    if (!not_found[PWD])
        set_pwd(ush);
    if (!not_found[SHLVL]) {
        ush->export = add_var(ush->export, "SHLVL=1");
        ush->env = add_var(ush->env, "SHLVL=1");
    }
    if (!not_found[PATH] || !not_found[TERM] || !not_found[HOME])
        ush->local_variables = set_local(ush->local_variables, not_found);
}
