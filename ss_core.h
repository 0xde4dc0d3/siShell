#ifndef SS_CORE_H
#define SS_CORE_H

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
void ss_exec(const char *command);

#endif // !SS_CORE_H
