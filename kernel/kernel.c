#include "kernel.h"


void kernel_main() {
    isr_install();
    irq_install();

    kprint("Type help for options\n> ");
}

void user_input(char *input) {
    if (strcmp(input, "end") == 0) {
        shutdown();
    } else if (strcmp(input, "test page") == 0) {
        testKmalloc();
    } else if (strcmp(input, "help") == 0) {
        help();
    } else if (strcmp(input, "test store")) {
        testStorage();
    } else if (strcmp(input, "drivers") == 0 ){
        listDrivers();
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}