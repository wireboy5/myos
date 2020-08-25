#include "commands.h"

void shutdown() {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
}

void help() {
        kprint("help - Show this page\n");
        kprint("end - Halt the CPU\n");
        kprint("test page - Test the Kmalloc function\n");
        kprint("test store - Test the booted storage medium\n");
        kprint("drivers - List all installed drivers (Nonfunctional)\n");
}

void testKmalloc(){
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
}

void testStorage(){}

void listDrivers(){}