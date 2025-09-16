#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ss_utils.h"

/**
    * @brief retrive only the name of the current dir, used in ss_display_prompt
    * @param *ss_info the struct containing all the siShell info
    FIXME: I think all this can be done in the while loop, I'm too lazy now
 */
void ss_get_cwd_name(SS_INFO *ss_info) {
    int idx = (int)strlen(ss_info->abs_cwd);
    int count = 0;
    while (ss_info->abs_cwd[--idx] != '/') count++;
    for (int i = 0; i < count; ++i) {
        ss_info->cwd_name[i] = ss_info->abs_cwd[(idx+1)+i];
    }
}

/**
    * @brief read user input from stdin 
    * @return char* a string containig user commmand or NULL
 */ 
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
