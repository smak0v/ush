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
