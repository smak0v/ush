#include "libmx.h"

int mx_printnbr(int i) {
    return (write(0, &i, 1));
}
