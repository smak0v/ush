#include "ush.h"

static char **build_export_args(char *key, char *value) {
    char **export = mx_memalloc(sizeof(char *) * 3);

    export[0] = mx_strdup("export");
    export[1] = mx_build_key_value_str(key, value);
    export[2] = NULL;

    return export;
}

static void export(t_ush *ush, char *key, char *value) {
    char **export = build_export_args(key, value);

    mx_overwrite_strarr_value(&ush->hidden, key, value);
    mx_ush_export(export, ush);
    mx_del_strarr(&export);
}

static char includes_link(char *pwd, char *destination) {
    char **split = mx_strsplit(destination, '/');
    char *path = NULL;
    char *full_path = NULL;

    while (split[0]) {
        path = mx_strarr_to_str(split, "/");
        if (destination[0] == '/')
            full_path = mx_strjoin("/", path);
        else
            full_path = mx_build_path(pwd, path);
        if (mx_check_link(&path, full_path)) {
            mx_del_strarr(&split);
            mx_strdel(&full_path);
            return 1;
        }
        mx_strdel(&split[mx_strarr_len(split) - 1]);
        mx_strdel(&full_path);
    }
    free(split);
    return 0;
}

char mx_check_link(char **path, char *full_path) {
    struct stat st;

    mx_strdel(path);
    if (lstat(full_path, &st) != -1 && MX_IS_LNK(st.st_mode))
        return 1;

    return 0;
}

int mx_cd(t_ush *ush, char **flags, char *destination) {
    char *path = NULL;
    char *pwd = mx_getenv(ush->hidden, "PWD");
    char *real_path = NULL;

    if (mx_check_flag(flags, 's') && includes_link(pwd, destination))
        return mx_cd_not_a_directory_error(&pwd, destination);
    real_path = realpath(destination, NULL);
    if (chdir(destination) == -1) {
        mx_strdel(&real_path);
        return mx_cd_no_such_file_or_dir(&pwd, destination);
    }
    else {
        path = mx_check_flag(flags, 'P') ? mx_get_pwd()
               : mx_strdup(mx_build_logical_path(pwd, destination, real_path));
        export(ush, "OLDPWD", pwd);
        export(ush, "PWD", path);
        mx_strdel(&real_path);
        mx_strdel(&pwd);
        mx_strdel(&path);
    }
    return 0;
}
