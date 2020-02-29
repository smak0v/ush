#include "ush.h"

int mx_check_identifier_validity(char *str, int ravno) {
    for (int i = 0; str[i]; ++i) {
        if (!mx_isalpha(str[i]) && !mx_isdigit(str[i]) && str[i] != '_') {
            if (str[i] == '=' && ravno)
                continue;
            return 1;
        }
    }
    return 0;
}
