#ifndef SS_UTILS_H
#define SS_UTILS_H

#include "ss_visual.h"

#define SS_STDIN_LINE_LEN 128

#define MIN(a, b) ((a < b)?(a):(b))

/**
    * @brief retrive only the name of the current dir, used in ss_display_prompt
    * @param ss_info the struct containing all the siShell info
    FIXME: I think all this can be done in the while loop, I'm too lazy now
*/
char *ss_get_cwd_name(SS_INFO ss_info);

/**
    * @brief read user input from stdin 
    * @return char* a string containig user commmand or NULL
*/ 
char *ss_read_line(void);

/**
    * @brief levenshtein_distance used to find the best match between two commands
    * @param str_1 first command 
    * @param str_2 second command
    * @return distance number of editing operation to transform str_1 in str_2
*/ 
int levenshtein_distance(const char *str_1, const char *str_2);

/**
    * @brief find the command in ss_builtin that is most similar to the one entered by the user
    * @param str the command entered by the user
    * @return idx of the best match in ss_builtin
*/ 
int get_closest_one(const char *str);

#endif // !SS_UTILS_H
