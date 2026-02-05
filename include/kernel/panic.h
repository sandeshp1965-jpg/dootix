#ifndef PANIC_H
#define PANIC_H

#include <arch/platform/vga.h>

void panic_handler(const my_uchar* code);

#endif