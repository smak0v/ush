#include "ush.h"

char *mx_get_pwd(void) {
    long size = pathconf(".", _PC_PATH_MAX);
    char *path = mx_strnew(size);

    getcwd(path, (size_t)size);
    return path;
}

char *mx_build_pwd_str(void) {
    char *path = mx_get_pwd();
    char *res = mx_strjoin("PWD=", path);

    mx_strdel(&path);
    return res;
}
