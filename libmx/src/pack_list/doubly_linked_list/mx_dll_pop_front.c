#include "libmx.h"

void mx_dll_pop_front(t_dll **head) {
    t_dll *p = NULL;

    if (!head || !(*head))
        return;
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
    }
    else {
        p = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(p);
        p = NULL;
    }
}
