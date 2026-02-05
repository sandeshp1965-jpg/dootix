#ifndef SERIAL_H
#define SERIAL_H

#include <kernel/types.h>
#include <arch/io.h>

#define COM1_PORT 0x3f8

my_int init_serial();

my_int is_transmit_empty();

void my_serial_putc(my_char a);

void my_serial_putstr(const my_char* str);

void my_serial_puthex(uint32_t val);

#endif