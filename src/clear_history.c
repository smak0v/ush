#include "ush.h"

void mx_clear_history(t_list **history) {
    while (history && *history) {
        free((*history)->data);
        mx_pop_front(history);
    }
}
