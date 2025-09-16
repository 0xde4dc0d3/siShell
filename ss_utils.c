#include "ss_utils.h"
#include <string.h>

/**
    * @brief retrive only the name of the current dir, used in ss_display_prompt
    * @param *ss_info the struct containing all the siShell info
    FIXME: I think all this can be done in the while loop, I'm too lazy now
 */
void ss_get_cwd_name(SS_INFO *ss_info) {
    int idx = (int)strlen(ss_info->abs_cwd);
    int count = 0;
    while (ss_info->abs_cwd[--idx] != '/') count++;
    for (int i = 0; i < count; ++i) {
        ss_info->cwd_name[i] = ss_info->abs_cwd[(idx+1)+i];
    }
}
