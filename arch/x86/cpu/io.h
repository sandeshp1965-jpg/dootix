#ifndef IO_H
#define IO_H

#include <kernel/types.h>

//static
static inline void outb(my_ushort PORT, my_uchar value){
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(PORT));
}

static inline my_uchar inb(my_ushort PORT){
    my_uchar ret;
    //=a, puts the value in A registers, while Nd means direct access in the D registers
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(PORT));
    return ret;
}

#endif