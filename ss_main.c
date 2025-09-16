#include <stdlib.h>
#include "ss_init.h"
#include "ss_core.h"

int main(int argc, const char **argv) {
    // Shell startup
    SS_INFO ss_info;
    ss_init(&ss_info);
    //ss_display_prompt(ss_info);
    // Loop
    //ss_exec(argv[1]);
    ss_loop(ss_info);
    // Exit 
    exit(EXIT_SUCCESS);
}
