#include "ush.h"

static void push_back_proccess(t_process **processes, t_process *process) {
    t_process *last = *processes;

    if (!*processes) {
        *processes = process;
        return;
    }
    while (last->next)
        last = last->next;
    last->next = process;
}

static t_process *create_process(char *cmd) {
    t_process *process = calloc(1, sizeof(t_process));

    process->argv = mx_split_cmd(cmd);
    return process;
}

t_process *mx_create_processes(char *cmd) {
    char **splited_by_pipes = mx_strsplit(cmd, '|');
    char **tmp = splited_by_pipes;
    char *trimmed = NULL;
    t_process *processes = NULL;

    while (*tmp) {
        trimmed = mx_strtrim(*tmp);
        push_back_proccess(&processes, create_process(trimmed));
        mx_strdel(&trimmed);
        ++tmp;
    }
    mx_del_strarr(&splited_by_pipes);
    return processes;
}

void mx_delete_processes(t_process **processes) {
    t_process *curr = *processes;
    t_process *next = NULL;

    while (curr) {
        next = curr->next;
        mx_del_strarr(&curr->argv);
        free(curr);
        curr = NULL;
        curr = next;
    }
    *processes = NULL;
}
