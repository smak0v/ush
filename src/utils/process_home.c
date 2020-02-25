#include "ush.h"

static char *get_homepath(void) {
    uid_t uid = getuid();
    struct passwd *pw = (uid == -1 && errno ? NULL : getpwuid (uid));

    if (!pw)
        return mx_strdup("/");
    else
        return mx_strjoin("HOME=/Users/", pw->pw_name);
}

char **mx_process_home(char **arr) {
    char *home[] = {get_homepath(), NULL};
    char **tmp = arr;

    arr = mx_strarr_join(arr, home);
    mx_del_strarr(&tmp);

    return arr;
}
