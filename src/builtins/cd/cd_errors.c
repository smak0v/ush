#include "ush.h"

int mx_cd_not_a_directory_error(char **delstr, char *destination) {
    mx_print_error("cd: not a directory: ");
    mx_print_error_endl(destination);
    mx_strdel(delstr);

    return 1;
}
