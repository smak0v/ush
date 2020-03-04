#include "ush.h"

char *mx_get_homepath(void) {
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (!pw || !pw->pw_name)
        return mx_strdup("/");
    else
        return mx_strjoin("/Users/", pw->pw_name);

}

static char *mx_get_homepath_key_value(void) {
    char *path = mx_get_homepath();
    char *res = mx_strjoin("HOME=", path);

    mx_strdel(&path);
    return res;
}

char **mx_process_home(char **arr) {
    char *home[] = {mx_get_homepath_key_value(), NULL};
    char **tmp = arr;

    arr = mx_strarr_join(arr, home);
    mx_del_strarr(&tmp);
    mx_strdel(&home[0]);

    return arr;
}
