#ifndef IDT_H
#define IDT_H

#include <kernel/types.h>

typedef struct InterruptDescription64 {
    my_ushort offset_low;      // 0-15
    my_ushort selector;        // 16-31
    my_uchar  ist;             // 32-39 (bits 0-2 are IST)
    my_uchar  type_attributes; // 40-47
    my_ushort offset_mid;      // 48-63
    my_uint   offset_high;     // 64-95
    my_uint   reserved;        // 96-127 (This MUST be 32-bit)
} __attribute__((packed)) InterruptDescription64;

#define IDT_ENTRIES 256
extern InterruptDescription64 idt[IDT_ENTRIES];

typedef struct IDTPtr {
    my_ushort limit;
    my_u64 base;
} __attribute__((packed)) IDTPtr;

extern IDTPtr idt_ptr_struct;

void idt_init();
void idt_install_keyboard(void);

void set_idt_gate(my_uint n, my_u64 handler, my_ushort selector, my_char flags);


#endif