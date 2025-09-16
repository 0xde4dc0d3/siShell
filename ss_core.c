#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ss_core.h"
#include "ss_builtin.h"
#include "ss_visual.h"

/**
    * @brief Execute a command located in /bin directory
    * @param command the command specified by the user 
*/
void ss_exec_bin(const char *command) {
    char path[256];
    snprintf(path, sizeof(path), "/bin/%s", command);

    if (execl(path, command, (char*)((void*)0)) == -1) {
        perror("Execl error");
        exit(EXIT_FAILURE);
    }
}

/**
    * @brief check for the command, if it exists, nature then execute it 
    * @param command the command entered by the user
    FIXME: need a better implementation of this, using wait() and fork() to spawn a 
    new process when a command is called
*/
void ss_exec(const char *command) {
    if (command == NULL) {
        fprintf(stderr, "Command cannot be null.\n");
        exit(EXIT_FAILURE);
    }
    int idx = ss_is_builtin(command);
    if (idx != -1) (*ss_builtin_func[idx])();
    else ss_exec_bin(command);
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

/**
    * @brief main loop of siShell, read from stdin, parse the input and execute 
    * the command
    * @param ss_info the struct containig siShell info
*/ 
void ss_loop(SS_INFO ss_info) {
    char *stdin_line = NULL;
    do {
        ss_display_prompt(ss_info);
        stdin_line = ss_read_line();
        stdin_line[strlen(stdin_line) - 1] = 0;
        ss_exec(stdin_line);
    } while (1);
}
