#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "ss_core.h"
#include "ss_builtin.h"

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
