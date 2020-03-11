#include "ush.h"

bool mx_is_builtin(char *name, t_ush *ush) {
    for (int i = 0; i < MX_BUILTINS_COUNT; ++i)
        if (!mx_strcmp(name, ush->builtins[i]))
            return true;
    return false;
}
