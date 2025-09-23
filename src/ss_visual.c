#include <stdio.h>
#include <pwd.h>
#include "ss_visual.h"

void ss_display_prompt(SS_INFO ss_info) {
    printf(RED "[" RESET);
    printf("%s@%s ", ss_info.pw->pw_name, ss_info.hostname);
    printf(BLUE "%s" RESET, ss_info.cwd_name);
    printf(RED "]" RESET);
    printf("$ ");
}
