#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include "ss_init.h"
#include "ss_utils.h"

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
