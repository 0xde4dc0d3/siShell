#ifndef SS_CORE_H
#define SS_CORE_H

#include "ss_visual.h"

#define SS_STDIN_LINE_LEN 128

/**
    * @brief Execute a command located in /bin directory
    * @param command the command specified by the user 
*/
void ss_exec_bin(const char *command);

/**
    * @brief check for the command, if it exists, nature then execute it 
    * @param command the command entered by the user
    FIXME: need a better implementation of this, using wait() and fork() to spawn a 
    new process when a command is called
*/
void ss_exec(const char *command, SS_INFO ss_info);

/**
*/
void ss_launch(const char *command, SS_INFO ss_info);

/**
    * @brief main loop of siShell, read from stdin, parse the input and execute 
    * the command
    * @param ss_info the struct containig siShell info
*/ 
void ss_loop(SS_INFO ss_info);

#endif // !SS_CORE_H
