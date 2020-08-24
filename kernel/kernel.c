#include "../drivers/screen.h"

void main() {
    clear_screen();
    int i = 0;
    for (i = 0; i < 24; i++) {
        char str[255];
        int_to_ascii(i, str);
        kprint(str);
        kprint("\n");
    }
    kprint("Test!");
}
