#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ss_core.h"
#include "ss_builtin.h"
#include "ss_visual.h"
#include "ss_utils.h"

// TODO: ss_launch with fork() and wait()
// TODO: parsing stdin_line

/**
    * @brief Execute a command located in /bin directory
    * @param command the command specified by the user 
*/
void ss_exec_bin(const char *command) {
    char path[256];
    snprintf(path, sizeof(path), "/bin/%s", command);

    if (execl(path, command, (char*)((void*)0)) == -1) {
        perror("Execl error (no commmand found)");
    }
}

/**
    * @brief check for the command, if it exists, nature then execute it 
    * @param command the command entered by the user
    * @param ss_info the struct containig all siShell infos
    FIXME: need a better implementation of this, using wait() and fork() to spawn a 
    new process when a command is called
    It needs to be put inside ss_launch. Watch out for the exit()
*/
void ss_exec(const char *command, SS_INFO ss_info) {
    if (command == NULL) {
        fprintf(stderr, "Command cannot be null.\n");
        exit(EXIT_FAILURE);
    }
    int idx = ss_is_builtin(command);
    if (idx != -1) {
        // If the command require SS_INFO struct
        if (strcmp(command, "whoami") == 0) (*ss_builtin_func[idx])(&ss_info);
        else (*ss_builtin_func[idx])(((void*)0));
    } else {
        ss_exec_bin(command);
    }
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
        ss_exec(stdin_line, ss_info);
    } while (1);
}
