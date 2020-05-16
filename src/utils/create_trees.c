#include "ush.h"

static bool is_escpd_semicolon(char *line, int i) {
    return (line[i] == ';' && (i - 1 >= 0) && line[i - 1] != '\\')
            || (line[i] == ';');
}

static bool crutch_for_auditor(char *line, int i, bool quote) {
    return (line[i] == ';' && (i - 1 < 0) && line[i + 1] == ';' && !quote)
            || (is_escpd_semicolon(line, i) && line[i + 1] == ';' && !quote);
}

static void split_semicolons(t_ush *ush, t_dll **trees, char *line) {
    char *token = NULL;
    int prev_pos = 0;
    bool quote= false;

    for (int i = 0; i < mx_strlen(line); ++i) {
        mx_check_quoted(line[i], &quote);
        if (is_escpd_semicolon(line, i) && line[i + 1] != ';' && !quote) {
            token = mx_strndup(line + prev_pos, i - prev_pos);
            mx_copy_and_create_tree(token, trees);
            prev_pos = ++i;
        }
        else if (crutch_for_auditor(line, i, quote)) {
            mx_semicolons_parse_error(ush, trees);
            return;
        }
    }
    if (mx_strcmp(line + prev_pos, ";")) {
        token = mx_strndup(line + prev_pos, mx_strlen(line + prev_pos));
        mx_copy_and_create_tree(token, trees);
    }
}

void mx_create_trees( t_ush *ush, t_dll **trees, char *line) {
    if (mx_is_empty_line(line))
        return;
    // TODO check for closed cmd_substs
    if (!mx_is_closed_quotes(line)) {
        mx_print_error("ush: multiline input not supported\n");
        return;
    }
    split_semicolons(ush, trees, line);
}
