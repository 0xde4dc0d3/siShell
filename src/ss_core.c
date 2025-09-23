#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "ss_core.h"
#include "ss_builtin.h"
#include "ss_visual.h"
#include "ss_utils.h"

// TODO: parsing stdin_line

void ss_exec_bin(const char *command) {
    char path[256];
    snprintf(path, sizeof(path), "/bin/%s", command);

    if (execl(path, command, (char*)((void*)0)) == -1) {
        perror("Specified command do not exists");
    }
}

void ss_launch(const char *command, SS_INFO ss_info) {
    pid_t pid;
    
    pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        ss_exec(command, ss_info);
    } else {
        waitpid(pid, NULL, 0);
    }
}

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

void ss_loop(SS_INFO ss_info) {
    char *stdin_line = NULL;
    do {
        ss_display_prompt(ss_info);
        stdin_line = ss_read_line();
        stdin_line[strlen(stdin_line) - 1] = 0;
        ss_launch(stdin_line, ss_info);
    } while (1);
}
