#include "ush.h"

void mx_env_janitor(t_env **env_struct) {
    t_env *env = *env_struct;

    mx_strdel(&env->P);
    mx_strdel(&env->u);
    mx_del_strarr(&env->name_val);
    mx_del_strarr(&env->util);

    free(*env_struct);
    *env_struct = NULL;
}

char **find_and_clean(char **res, char **split, int i, int *flag) {
    char **test_split = NULL;
    char *value = NULL;

    for (int j = i + 1; res[j]; j++) {
        test_split = mx_split_key_value(res[j]);

        if (mx_strcmp(split[0], test_split[0]) == 0) {
            value = mx_strdup(res[j]);
            res = mx_pop_string_array(res, value);
            mx_strdel(&res[i]);
            res[i] = value;
            j--;
            *flag = 1;
        }

        mx_del_strarr(&test_split);
    }

    return res;
}

char **mx_clean_duplicates(char **env) {
    char **split = NULL;
    char **res = env;

    for (int i = 0; res && res[i + 1]; i++) {
        int flag = 0;

        split = mx_split_key_value(res[i]);
        res = find_and_clean(res, split, i, &flag);
        mx_del_strarr(&split);

        if (flag)
            i--;
    }

    return res;
}
