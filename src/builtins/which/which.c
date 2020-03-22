#include "ush.h"

static char *get_full_filename(char *dirpath, char *filename) {
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
            full_filename = get_full_filename(path, command);
            lstat(full_filename, &st);

            if (MX_IS_EXEC(st.st_mode)) {
                found = 1;
                if (!mx_check_flag(flags, 's'))
                    mx_printstr_endl(full_filename);
                if (!mx_check_flag(flags, 'a')) {
                    mx_strdel(&full_filename);
                    break;
                }
            }
            mx_strdel(&full_filename);
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

        closedir(dir);
    }

    return found;
}

static char check_builtins(t_ush *ush, char *arg) {
    for (int i = 0; ush->builtins[i]; ++i) {
        if (!mx_strcmp(arg, ush->builtins[i])) {
            mx_printstr(arg);
            mx_printstr_endl(": shell built-in command");
            return 1;
        }
    }
    return 0;
}

void mx_which(t_ush *ush, char **flags, char **args, int *status) {
    char *env_path = NULL;
    char **path = NULL;

    env_path = getenv("PATH");
    if (!env_path)
        env_path = mx_getenv(ush->local_variables, "PATH");
    else
        env_path = mx_strdup(env_path);
    path = mx_strsplit(env_path, ':');

    for (int j = 0; args[j]; ++j) {
        if (check_builtins(ush, args[j]) && !mx_check_flag(flags, 'a'))
            continue;
        if (scan_dir(flags, path, args[j]) == 0)
            *status = 1;
    }

    mx_del_strarr(&path);
    mx_strdel(&env_path);
}
