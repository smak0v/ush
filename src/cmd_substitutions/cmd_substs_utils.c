#include "ush.h"

void mx_change_line(char **line, char **new_cmd_subst, int start, int end) {
    char *new_line = mx_strndup((*line), start);
    char *tmp = mx_strjoin(new_line, *new_cmd_subst);

    mx_strdel(&new_line);
    new_line = tmp;
    tmp = mx_strjoin(new_line, (*line) + start + end + 1);
    mx_strdel(&new_line);
    new_line = tmp;
    mx_strdel(line);
    *line = new_line;
    mx_strdel(new_cmd_subst);
}

char *mx_del_extra_cmd_subst_spaces(t_ush *ush, char *cmd_subst) {
    char *new_cmd_subst = mx_strnew(0);
    int j = 0;

    for (int i = 0; i < mx_strlen(cmd_subst) - 1; ++i) {
        new_cmd_subst = realloc(new_cmd_subst, mx_strlen(new_cmd_subst) + 2);
        if (mx_isspace(cmd_subst[i])) {
            new_cmd_subst[j] = ' ';
            while (mx_isspace(cmd_subst[i]))
                ++i;
            --i;
        }
        else
            new_cmd_subst[j] = cmd_subst[i];
        new_cmd_subst[++j] = '\0';
    }
    remove(ush->cmd_substs_file);
    mx_strdel(&cmd_subst);
    return new_cmd_subst;
}

bool mx_check_double_quote(int index, char *line) {
    --index;

    while (mx_isspace(line[index]) && (index >= 0))
        --index;

    return (line[index] == '"') ? true : false;
}

bool mx_check_single_quote(int index, char *line) {
    --index;

    while (mx_isspace(line[index]) && (index >= 0))
        --index;

    return (line[index] == '\'') ? true : false;
}

int mx_count_back_slashes(int level) {
    if (level == 0 || level == 1)
        return level;

    return (mx_pow(2, level - 1) * 2) - 1;
}

bool mx_check_back_slashes_count(int level, char *line, int start) {
    int back_slashes_count = mx_count_back_slashes(level);

    while (back_slashes_count) {
        if (line[--start] != '\\')
            return false;
        --back_slashes_count;
    }
    return true;
}
