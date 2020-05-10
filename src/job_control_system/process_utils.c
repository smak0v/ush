#include "ush.h"

t_process *create_process(char *cmd) {
    t_process *process = calloc(1, sizeof(t_process));

    process->argv = mx_split_cmd(cmd);
    return process;
}

t_process *mx_create_processes(char *cmd) {
    char **splited_by_pipes = mx_strsplit(cmd, '|');
    char **tmp = splited_by_pipes;
    char *copy = NULL;
    t_process *processes = NULL;

    while (*tmp) {
        copy = mx_strdup(*tmp);
        push_back_proccess(&processes, create_process(copy));
        mx_strdel(&copy);
        ++tmp;
    }
    mx_del_strarr(&splited_by_pipes);
    return processes;
}

void push_back_proccess(t_process **processes, t_process *process) {
    t_process *last = *processes;

    if (!*processes) {
        *processes = process;
        return;
    }
    while (last->next)
        last = last->next;
    last->next = process;
}

t_process *mx_copy_processes(t_process *processes) {
    t_process *tmp = processes;
    t_process *new_processes = NULL;
    t_process *process = NULL;

    while (tmp) {
        process = calloc(1, sizeof(t_process));
        process->argv = mx_strarr_dup(tmp->argv);
        process->pid = tmp->pid;
        process->status = tmp->status;
        push_back_proccess(&new_processes, process);
        tmp = tmp->next;
    }
    return new_processes;
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
