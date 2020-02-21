#include "ush.h"

t_env *mx_parse_env(char **args) {
    t_env *setup = mx_memalloc(sizeof(t_env));

    for (int i = 0; args[i]; i++) {
        if (args[i][0] == '-') {
            for (int j = 1; args[i][j]; j++) {
                if (args[i][j] != 'i' && args[i][j] != 'P' 
                    && args[i][j] != 'u') {
                    setup->error = args[i][j];
                    return setup;
                }
                if (args[i][j] == 'P') {
                    
                }
            }
        }
    }

    return setup;
}
