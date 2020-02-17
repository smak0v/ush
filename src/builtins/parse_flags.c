#include "ush.h"

static int count_separated_flags(int argc, char **argv) {
    int separated_flags_count = 0;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (mx_strlen(argv[i]) == 1)
                break;
            if ((argv[i][1] == '-') && (mx_strlen(argv[i]) == 2))
                break;
            ++separated_flags_count;
            continue;
        }
        break;
    }
    return separated_flags_count;
}

static int count_flags(int separated_flags_count, char **argv) {
    int flags_count = 0;

    for (int i = 1; i <= separated_flags_count; ++i)
        flags_count += mx_strlen(argv[i]) - 1;
    return flags_count;
}

static char **store_flags(int separated_flags_count, char **argv) {
    int flags_count = count_flags(separated_flags_count, argv);
    char **flags = (char **)malloc(sizeof(char *) * (++flags_count));
    int k = -1;

    for (int i = 1; i <= separated_flags_count; ++i)
        for (int j = 1; j < mx_strlen(argv[i]); ++j)
            flags[++k] = mx_strndup(&argv[i][j], 1);
    flags[++k] = NULL;
    return flags;
}

char **mx_store_flags(int argc, char **argv) {
    return store_flags(count_separated_flags(argc, argv), argv);
}
