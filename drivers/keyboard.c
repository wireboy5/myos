#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"
#include <stdint.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LSHIFT 0x2A
#define LSHIFTUP 0xAA
#define RSHIFT 0x36
#define RSHIFTUP 0x6C

static char key_buffer[256];

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "q", "q", "e", 
        "r", "t", "y", "u", "i", "o", "p", "[", "]", "Enter", "Lctrl", 
        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`", 
        "LShift", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char *shifted_sc_name[] = { "ERROR", "Esc", "!", "@", "#", "$", "%", "^", 
    "&", "*", "(", ")", "_", "+", "Backspace", "Tab", "Q", "W", "R", 
        "Y", "U", "Y", "U", "I", "O", "P", "{", "}", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ":", "\"", "~", 
        "LShift", "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", 
        "?", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};
const char shifted_sc_ascii[] = { '?', '?', '!', '@', '#', '$', '%', '^',     
    '&', '*', '(', ')', '_', '+', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '{', '}', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ':', '\"', '`', '?', '|', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', '<', '>', '?', '?', '?', '?', ' '};

uint8_t isShifted = 0;

static void keyboard_callback(registers_t *regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    uint8_t scancode = port_byte_in(0x60);
    //
    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        kprint_backspace();
    } else if (scancode == ENTER) {
        kprint("\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
    } else if (scancode == RSHIFT || scancode == LSHIFT) {
        isShifted = 1;
    } else if (scancode == RSHIFT + 0x80 || scancode == LSHIFT + 0x80) {
        isShifted = 0;
    } else if (scancode > SC_MAX) {
        return;
    } else {
        char letter;
        if(isShifted){
            letter = shifted_sc_ascii[(int)scancode];
        } else {
            letter = sc_ascii[(int)scancode];
        }
        /* Remember that kprint only accepts char[] */
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
