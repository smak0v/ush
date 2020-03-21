#include "ush.h"

int mx_check_flag(char **flags, char flag) {
    if (!flags)
        return 0;

    for (int i = 0; flags[i]; ++i) {
        if (*flags[i] == flag)
            return 1;
    }
    return 0;
}
