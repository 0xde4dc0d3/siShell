#ifndef SS_VISUAL_H
#define SS_VISUAL_H

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define BLUE    "\x1b[34m"
#define RESET   "\x1b[0m"

/**
    * @brief a struct containing all the sishell infos
*/
typedef struct {
    char            hostname[64];
    struct passwd   *pw;
    char            abs_cwd[64];    // absolute path of the cwd   
    char            cwd_name[64];   // only the cwd name
} SS_INFO;

/** 
    * @brief display sishell prompt
*/
void ss_display_prompt(SS_INFO ss_info);

#endif // !SS_VISUAL_H
