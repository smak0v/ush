#include "ush.h"

static char *rebuild_path(char **split, char *full_path, char **realpath) {
    char *real_name = mx_strnew(100);
    char *tmp = NULL;
    int size = readlink(full_path, real_name, 100);

    if (size > 0) {
        tmp = mx_replace_substr(*realpath,
                                real_name,
                                split[mx_strarr_len(split) - 1]);
    }

    mx_strdel(&real_name);
    return tmp;
}

char *mx_build_logical_path(char *pwd, char *dest, char *realpath) {
    char **dest_split = mx_strsplit(dest, '/');
    char *path = NULL;
    char *full_path = NULL;

    while (dest_split[0]) {
        path = mx_strarr_to_str(dest_split, "/");
        if (dest[0] == '/')
            full_path = mx_strjoin("/", path);
        else
            full_path = mx_build_path(pwd, path);
        if (mx_check_link(&path, full_path)) {
            realpath = rebuild_path(dest_split, full_path, &realpath);
        }
        mx_strdel(&dest_split[mx_strarr_len(dest_split) - 1]);
        mx_strdel(&full_path);
    }

    free(dest_split);
    return mx_strdup(realpath);
}
