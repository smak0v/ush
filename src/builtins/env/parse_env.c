#include "ush.h"

static int save_P(t_env *setup, char **args, int i, int j) {
    int step = 1;

    if (setup->P)
        mx_strdel(&(setup->P));
    if (args[i][j + 1] == '\0') {
        if (!args[i + 1]) {
            setup->P = mx_strdup("No ArGuMeNt");
            return 0;
        }
        setup->P = mx_strdup(args[i + 1]);
    }
    else {
        char *str = mx_memchr(args[i], 'P', (size_t)mx_strlen(args[i]));

        setup->P = mx_strdup(++str);
        step = 0;
    }
    return step;
}

static int process_flags(t_env *setup, char **args, int *i) {
    int step = 0;

    for (int j = 1; args[*i][j]; j++) {
        if (args[*i][j] != 'i' && args[*i][j] != 'P' 
            && args[*i][j] != 'u') {
            setup->error = args[*i][j];
            return 1;
        }
        if (args[*i][j] == 'i')
            setup->i = true;
        if (args[*i][j] == 'P') {
            step = save_P(setup, args, i, j);
            *i += step;
            break;
        }
    }

    return 0;
}

t_env *mx_parse_env(char **args) {
    t_env *setup = mx_memalloc(sizeof(t_env));
    int step = 0;
    int flag_stop = 0;

    for (int i = 0; args[i]; i++) {
        if (!mx_strcmp("--", args[i]))
            flag_stop = 1;
        else if (args[i][0] == '-' && !flag_stop)
            if (process_flags(setup, args, &i) == 1)
                return setup;
    }

    return setup;
}
