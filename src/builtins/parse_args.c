#include "ush.h"

static char *handle_escape(char *str1, char *str2) {
    char *tmp = NULL;
    char *res = NULL;

    res = mx_strndup(str1, (size_t)mx_strlen(str1) - 1);
    tmp = mx_strjoin(res, " ");
    mx_strdel(&res);
    res = mx_strjoin(tmp, str2);
    mx_strdel(&tmp);

    return res;
}

static char **store_files(int files_count, int flags, char **argv) {
    char **files = NULL;
    int j = -1;

    if (files_count) {
        files = (char **)malloc(sizeof(char *) * (++files_count));
        for (int i = flags + 1; argv[i]; ++i) {
            if (argv[i][mx_strlen(argv[i]) - 1] == 92 && argv[i + 1]) {
                files[++j] = handle_escape(argv[i], argv[i + 1]);
                i++;
            }
            else {
                files[++j] = mx_strdup(argv[i]);
            }
        }
        files[++j] = NULL;
    }
    return files;
}

static int count_files(char **argv, int flags_count) {
    int count = 0;

    for (int i = flags_count + 1; argv[i]; ++i)
        ++count;
    return count;
}

static int count_flags_with_stop_flag(char **argv) {
    int count = 0;

    for (int i = 1; argv[i]; ++i) {
        if (argv[i][0] == '-') {
            if (mx_strlen(argv[i]) == 1)
                break;
            if ((argv[i][1] == '-') && (mx_strlen(argv[i]) == 2)) {
                ++count;
                break;
            }
            ++count;
            continue;
        }
        break;
    }
    return count;
}

char **mx_store_files(char **argv) {
    int flags_count = count_flags_with_stop_flag(argv);
    int files_count = count_files(argv, flags_count);

    return store_files(files_count, flags_count, argv);
}
