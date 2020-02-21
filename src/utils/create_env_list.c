#include "ush.h"

t_list *mx_create_env_list(char **environ) {
    // t_list *env_list = NULL;
    // t_env *env = NULL;
    // char **tmp = NULL;

    // while (*environ) {
    //     tmp = mx_strsplit(*environ, '=');
    //     env = mx_memalloc(sizeof(t_env));
    //     env->key = mx_strdup(tmp[0]);
    //     if (!mx_strcmp(env->key, "SHLVL")) {
    //         env->value = mx_itoa(mx_atoi(tmp[1]) + 1);
    //         setenv(env->key, env->value, 1);
    //     }
    //     else
    //         env->value = mx_strdup(tmp[1]);
    //     mx_del_strarr(&tmp);
    //     mx_push_back(&env_list, env);
    //     environ++;
    // }
    // return env_list;

    mx_printstr_endl("create_env_list function can be deleted but i left it just in case. yulia xoxox");
}
