#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ss_utils.h"

char *ss_get_cwd_name(SS_INFO ss_info) {
    int idx = (int)strlen(ss_info.abs_cwd);
    int count = 0;
    char *cwd_name = (char*)malloc(64);
    if (!cwd_name) {
        perror("ss_get_cwd_name malloc error");
        exit(EXIT_FAILURE);
    }
    while (ss_info.abs_cwd[--idx] != '/') count++;
    for (int i = 0; i < count; ++i) {
        cwd_name[i] = ss_info.abs_cwd[(idx+1)+i];
    }
    return cwd_name;
}

char *ss_read_line(void) {
    char *stdin_line = NULL;
    size_t ss_stdin_line_len = SS_STDIN_LINE_LEN;
    
    if (getline(&stdin_line, &ss_stdin_line_len, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("getline error");
            exit(EXIT_FAILURE);
        }
    }
    return stdin_line;
}
