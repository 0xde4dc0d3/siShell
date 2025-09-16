#ifndef SS_BUILTIN_H
#define SS_BUILTIN_H

/**
    * This header file contains all the variables and functions related
    * to the builtin commands of the siShell.
*/

/**
    * @brief builtin commands list and relative list lenght
*/
extern const char *ss_builtin[];
#define SS_BUILTIN_LEN (sizeof(ss_builtin)/sizeof(char*))

/**
    * @brief list of functions for siShell's builtin commands
    * TODO: for now cat and echo
*/
void ss_ls(void);

/** 
    * @brief array of bultin functions
    * void: functions do not return nothing
    * (*...)(void): a pointer to a function that does not takes any arguments
    * ss_builtin_func[]: an array of this pointers
    * &ss_funcion_name: the address of the function
*/
extern void (*ss_builtin_func[])(void);

/**
    * @brief check if a command is or not a builtin command
    * @param command the command entered by the user
    * @return i (builtin command idx in the array) -1 (not a builtin command)
*/
int ss_is_builtin(const char *command);

#endif // !SS_BUILTIN_H
