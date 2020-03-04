#include "ush.h"

int mx_check_identifier_validity(char **strarr, int ravno) {
    char *str = strarr[0];

    for (int i = 0; str[i]; ++i) {
        if (!mx_isalpha(str[i]) && !mx_isdigit(str[i]) && str[i] != '_') {
            if (str[i] == '=' && ravno)
                continue;
            mx_del_strarr(&strarr);
            return 1;
        }
    }
    return 0;
}

int mx_check_identifier_validity_unset(char *str, int ravno) {
    for (int i = 0; str[i]; ++i) {
        if (!mx_isalpha(str[i]) && !mx_isdigit(str[i]) && str[i] != '_') {
            if (str[i] == '=' && ravno)
                continue;
            return 1;
        }
    }
    return 0;
}
