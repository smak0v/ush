#include "ush.h"

static int check_flag(char **flags, char flag) {
    if (!flags)
        return 0;

    for (int i = 0; flags[i]; ++i) {
        if (*flags[i] == flag)
            return 1;
    }
    return 0;
}

static char *mx_get_full_filename(char *dirpath, char *filename) {
    char *tmp = NULL;
    char *full_filename = NULL;

    if (dirpath[mx_strlen(dirpath) - 1] == '/')
        full_filename =  mx_strjoin(dirpath, filename);
    else {
        tmp = mx_strjoin(dirpath, "/");
        full_filename = mx_strjoin(tmp, filename);
        mx_strdel(&tmp);
    }
    return full_filename;
}

static int check_match(DIR *dir, char **flags, char *path, char *command) {
    char *full_filename = NULL;
    struct dirent *dirnt;
    struct stat st;
    int found = 0;

    while ((dirnt = readdir(dir)) != NULL) {
        if (!mx_strcmp(dirnt->d_name, command)) {
            full_filename = mx_get_full_filename(path, command);
            lstat(full_filename, &st);

            if (MX_IS_EXEC(st.st_mode)) {
                found = 1;
                if (!check_flag(flags, 's'))
                    mx_printstr_endl(full_filename);
                if (!check_flag(flags, 'a'))
                    break;
            }
        }
    }

    return found;
}

static int scan_dir(char **flags, char **path, char *command) {
    int found = 0;

    for (int i = 0; path[i]; ++i) {
        DIR *dir = opendir(path[i]);

        if (!dir)
            continue;

        if (check_match(dir, flags, path[i], command) == 1 && found == 0)
            found = 1;
    }

    return found;
}

void mx_which(t_ush *ush, char **flags, char **args, int *status) {
    char *env_path = getenv("PATH") ? getenv("PATH")
                     : mx_getenv(ush->local_variables, "PATH");
    char **path = mx_strsplit(env_path, ':');

    for (int j = 0; args[j]; ++j) {
        if (scan_dir(flags, path, args[j]) == 0)
            *status = 1;
    }
}
