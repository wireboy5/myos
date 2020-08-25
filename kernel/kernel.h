


#ifndef KERNEL_H
#define KERNEL_H
#include <stdint.h>
#include <stddef.h>
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include "../drivers/screen.h"
#include "../kernelUtil/commands.h"

void user_input(char *input);

#endif