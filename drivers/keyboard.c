#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"


u8 lastKey;

void keyPress(char* msg, u8 scancode, u8 keyUp){
    kprint(msg);
    if (keyUp) {
        kprint(" Up");
    } else {
        kprint(" Down");
    }
    kprint("\n");
}

void print_letter(u8 scancode, u8 keyUp) {
    lastKey = scancode;
    u8 sc = scancode;
    if(keyUp == 1){
        sc = sc - 0x80;
    }
    switch (sc) {
        case 0x0:
            keyPress("ERROR", scancode, keyUp);
            break;
        case 0x1:
            keyPress("ESC", scancode, keyUp);
            break;
        case 0x2:
            keyPress("1", scancode, keyUp);
            break;
        case 0x3:
            keyPress("2", scancode, keyUp);
            break;
        case 0x4:
            keyPress("3", scancode, keyUp);
            break;
        case 0x5:
            keyPress("4", scancode, keyUp);
            break;
        case 0x6:
            keyPress("5", scancode, keyUp);
            break;
        case 0x7:
            keyPress("6", scancode, keyUp);
            break;
        case 0x8:
            keyPress("7", scancode, keyUp);
            break;
        case 0x9:
            keyPress("8", scancode, keyUp);
            break;
        case 0x0A:
            keyPress("9", scancode, keyUp);
            break;
        case 0x0B:
            keyPress("0", scancode, keyUp);
            break;
        case 0x0C:
            keyPress("-", scancode, keyUp);
            break;
        case 0x0D:
            keyPress("+", scancode, keyUp);
            break;
        case 0x0E:
            keyPress("Backspace", scancode, keyUp);
            break;
        case 0x0F:
            keyPress("Tab", scancode, keyUp);
            break;
        case 0x10:
            keyPress("Q", scancode, keyUp);
            break;
        case 0x11:
            keyPress("W", scancode, keyUp);
            break;
        case 0x12:
            keyPress("E", scancode, keyUp);
            break;
        case 0x13:
            keyPress("R", scancode, keyUp);
            break;
        case 0x14:
            keyPress("T", scancode, keyUp);
            break;
        case 0x15:
            keyPress("Y", scancode, keyUp);
            break;
        case 0x16:
            keyPress("U", scancode, keyUp);
            break;
        case 0x17:
            keyPress("I", scancode, keyUp);
            break;
        case 0x18:
            keyPress("O", scancode, keyUp);
            break;
        case 0x19:
            keyPress("P", scancode, keyUp);
            break;
		case 0x1A:
			keyPress("[", scancode, keyUp);
			break;
		case 0x1B:
			keyPress("]", scancode, keyUp);
			break;
		case 0x1C:
			keyPress("ENTER", scancode, keyUp);
			break;
		case 0x1D:
			keyPress("LCtrl", scancode, keyUp);
			break;
		case 0x1E:
			keyPress("A", scancode, keyUp);
			break;
		case 0x1F:
			keyPress("S", scancode, keyUp);
			break;
        case 0x20:
            keyPress("D", scancode, keyUp);
            break;
        case 0x21:
            keyPress("F", scancode, keyUp);
            break;
        case 0x22:
            keyPress("G", scancode, keyUp);
            break;
        case 0x23:
            keyPress("H", scancode, keyUp);
            break;
        case 0x24:
            keyPress("J", scancode, keyUp);
            break;
        case 0x25:
            keyPress("K", scancode, keyUp);
            break;
        case 0x26:
            keyPress("L", scancode, keyUp);
            break;
        case 0x27:
            keyPress(";", scancode, keyUp);
            break;
        case 0x28:
            keyPress("'", scancode, keyUp);
            break;
        case 0x29:
            keyPress("`", scancode, keyUp);
            break;
		case 0x2A:
			keyPress("LShift", scancode, keyUp);
			break;
		case 0x2B:
			keyPress("\\", scancode, keyUp);
			break;
		case 0x2C:
			keyPress("Z", scancode, keyUp);
			break;
		case 0x2D:
			keyPress("X", scancode, keyUp);
			break;
		case 0x2E:
			keyPress("C", scancode, keyUp);
			break;
		case 0x2F:
			keyPress("V", scancode, keyUp);
			break;
        case 0x30:
            keyPress("B", scancode, keyUp);
            break;
        case 0x31:
            keyPress("N", scancode, keyUp);
            break;
        case 0x32:
            keyPress("M", scancode, keyUp);
            break;
        case 0x33:
            keyPress(",", scancode, keyUp);
            break;
        case 0x34:
            keyPress(".", scancode, keyUp);
            break;
        case 0x35:
            keyPress("/", scancode, keyUp);
            break;
        case 0x36:
            keyPress("Rshift", scancode, keyUp);
            break;
        case 0x37:
            keyPress("Keypad *", scancode, keyUp);
            break;
        case 0x38:
            keyPress("LAlt", scancode, keyUp);
            break;
        case 0x39:
            keyPress("Spc", scancode, keyUp);
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            
            if (scancode <= 0x7f) {
                kprint("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                print_letter(scancode, 1);
            } else kprint("Unknown key up");
            break;
    }
}


static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);
    char *sc_ascii;
    //int_to_ascii(scancode, sc_ascii);
    //kprint("Keyboard scancode: ");
    //kprint(sc_ascii);
    //kprint(", ");
    print_letter(scancode,0);
    //kprint("\n");
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

