#include "libmx.h"

void mx_printstr_endl(const char *s) {
    if (s) {
        write(1, s, mx_strlen(s));
        mx_printchar('\n');
    }
}
