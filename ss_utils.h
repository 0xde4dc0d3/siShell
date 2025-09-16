#ifndef SS_UTILS_H
#define SS_UTILS_H

#include "ss_visual.h"

/**
    * @brief retrive only the name of the current dir, used in ss_display_prompt
    * @param *ss_info the struct containing all the siShell info
    FIXME: I think all this can be done in the while loop, I'm too lazy now
 */
void ss_get_cwd_name(SS_INFO *ss_info);

#endif // !SS_UTILS_H
