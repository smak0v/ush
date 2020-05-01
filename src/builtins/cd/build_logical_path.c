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

static char *process_path(char *dst, char *rlpath, char *pwd, int *lnk) {
    char **dstsplit = mx_strsplit(dst, '/');
    char *full_path = NULL;
    char *path = NULL;

    while (dstsplit[0]) {
        path = mx_strarr_to_str(dstsplit, "/");
        if (dst[0] == '/')
            full_path = mx_strjoin("/", path);
        else
            full_path = mx_build_path(pwd, path);
        if (mx_check_link(&path, full_path)) {
            rlpath = rebuild_path(dstsplit, full_path, &rlpath);
            *lnk = 1;
        }
        mx_strdel(&dstsplit[mx_strarr_len(dstsplit) - 1]);
        mx_strdel(&full_path);
    }
    free(dstsplit);
    return rlpath;
}

char *mx_build_logical_path(char *pwd, char *dest, char *realpath) {
    int link = 0;

    realpath = process_path(dest, realpath, pwd, &link);
    
    if (link)
        return realpath;
    else    
        return mx_strdup(realpath);
}
