#include "ush.h"

int mx_cd_not_a_directory_error(char **delstr, char *destination, char **str) {
    mx_strdel(str);
    mx_print_error("cd: not a directory: ");
    mx_print_error_endl(destination);
    mx_strdel(delstr);

    return 1;
}

int mx_cd_no_such_file_or_dir(char **delstr, char *destination) {
    mx_print_error("ush: cd: ");
    mx_print_error(destination);
    mx_print_error_endl(": No such file or directory");
    mx_strdel(delstr);

    return 1;
}

int mx_cd_invalid_option(char *option) {
    mx_print_error("bash: cd: -");
    mx_print_error(option);
    mx_print_error_endl(": invalid option");
    mx_print_error_endl("cd: usage: cd [-L|-P] [dir]");

    return 1;
}
