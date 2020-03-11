#include "ush.h"

static char *path_constructor(char *path, char *fname) {
    int len = mx_strlen(fname);
    char *path_with_slash = mx_strjoin(path, "/");
    char tmp[len];
    char *res = NULL;

    mx_strdel(&path);
    if (fname[len - 1] != '/')
        res = mx_strjoin(path_with_slash, fname);
    else {
        mx_strncpy(tmp, fname, len - 1);
        tmp[len - 1] = '\0';
        res = mx_strjoin(path_with_slash, tmp);
    }

    mx_strdel(&path_with_slash);
    return res;
}

char *mx_build_path(char *pwd, char *fname) {
    struct stat st;
    char *full_path = NULL;

    if (fname[0] == '/')
        full_path = mx_strdup(fname);
    else
        full_path = path_constructor(pwd, fname);

    return full_path;
}
