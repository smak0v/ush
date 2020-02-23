#include "ush.h"

static int save_arg(t_env *setup, char **args, int i, int j, char flag) {
    int step = 1;
    char *res = (flag == 'P') ? setup->P : setup->u;
    char *str = NULL;

    if (res)
        mx_strdel(&res);
    if (args[i][j + 1] == '\0')
        res = (!args[i + 1]) ? mx_strdup("No ArG") : mx_strdup(args[i + 1]);
    else {
        str = mx_memchr(args[i], flag, (size_t)mx_strlen(args[i]));
        res = mx_strdup(++str);
        step = 0;
    }
    if (flag == 'P')
        setup->P = res;
    else
        setup->u = res;
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
        if (args[*i][j] == 'P' || args[*i][j] == 'u' ) {
            step = save_arg(setup, args, *i, j, args[*i][j]);
            *i += step;
            break;
        }
    }
    return 0;
}

static int count_name_val(char **args) {
    int len = 0;
    int i = 0;

    while (args[i] && mx_get_char_index(args[i++], '=') != -1)
        len++;

    return len;
}

static int write_args(char **old_arr, t_env *setup) {
    int len = count_name_val(old_arr);
    int i = 0;
    
    setup->name_val = malloc(sizeof(char *) * (len + 1));
    while (i < len) {
        setup->name_val[i] = mx_strdup(old_arr[i]);
        i++;
    }

    setup->name_val[i] = NULL;

    return len;
}

t_env *mx_parse_env(char **args) {
    t_env *setup = mx_memalloc(sizeof(t_env));
    int flag_stop = 0;
    int name_val_len = 0;

    for (int i = 1; args[i]; i++)
        if (!mx_strcmp("--", args[i]))
            flag_stop = 1;
        else if (args[i][0] == '-' && flag_stop == 0) {
            if (process_flags(setup, args, &i) == 1)
                return setup;
        }
        else if (mx_get_char_index(args[i], '=') != -1) {
            flag_stop = 1;
            name_val_len = write_args(&args[i], setup);
            i += name_val_len - 1;
        }
        else {
            setup->util = mx_strarr_dup(&args[i]);
            break;
        }
    return setup;
}
