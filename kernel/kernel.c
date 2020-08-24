#include "../drivers/screen.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"
void main() {
    clear_screen();
    isr_install();
    asm volatile("sti");
    init_timer(50);
    init_keyboard();
    // int i = 0;
    // for (i = 0; i < 24; i++) {
    //     char str[255];
    //     int_to_ascii(i, str);
    //     kprint(str);
    //     kprint("\n");
    // }
    // kprint("Test!");
    
    
    // while(1){
    //     char str[255];
    //     int_to_ascii(getTick(),str);
    //     kprint_at(str,0,0);
    // };
}
