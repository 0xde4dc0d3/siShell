#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include "ss_builtin.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

// TODO: ss_core.c a - exec, loop...
// TODO: ss_visual.c - prompt style, customization,
// TODO: ss_utils.c - like ss_get_cwd_name
// TODO: ss_init.c - init, load ss_visual.c related stuff

/**
    * @brief a struct containing all the siShell infos
*/
typedef struct {
    char            hostname[64];
    struct passwd   *pw;
    char            abs_cwd[64];    // Absolute path of the cwd   
    char            cwd_name[64];   // Only the cwd name
} SS_INFO;

/**
    * @brief retrive only the name of the current dir, used in ss_display_prompt
    * @param *ss_info the struct containing all the siShell info
    FIXME: I think all this can be done in the while loop, I'm too lazy now
    UTILS
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
    * @brief retrive various informations like hostname and username
    * @param *ss_info a SS_INFO struct to be filled
    INIT
*/
void ss_init(SS_INFO *ss_info) {
    if (gethostname(ss_info->hostname, sizeof(ss_info->hostname)) == -1) {
        perror("gethostname error");
        exit(EXIT_FAILURE);
    }
    
    struct passwd *pw;
    uid_t uid = getuid();
    if ((pw = getpwuid(uid)) == NULL) {
        perror("getpwuid error");
        exit(EXIT_FAILURE);
    }
    ss_info->pw = pw;

    if (getcwd(ss_info->abs_cwd, sizeof(ss_info->abs_cwd)) == NULL) {
        perror("getcwd error");
        exit(EXIT_FAILURE);
    }
    ss_get_cwd_name(ss_info);
}

/** 
    * @brief display siShell prompt
    * VISUAL
*/
void ss_display_prompt(SS_INFO ss_info) {
    printf(RED "[" RESET);
    printf("%s@%s ", ss_info.pw->pw_name, ss_info.hostname);
    printf(BLUE "%s" RESET, ss_info.cwd_name);
    printf(RED "]" RESET);
    printf("$");
}

/**
    * @brief Execute a command located in /bin directory
    * @param command the command specified by the user 
    CORE
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
    CORE
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

int main(int argc, const char **argv) {
    // Shell startup
    SS_INFO ss_info;
    ss_init(&ss_info);
    ss_display_prompt(ss_info);
    // Loop
    ss_exec(argv[1]);
    // Exit 
    exit(EXIT_SUCCESS);
}
