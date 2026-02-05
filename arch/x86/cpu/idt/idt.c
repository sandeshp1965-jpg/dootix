#include "idt.h"
#include <arch/platform/serial.h>

#define IDT_ENTRIES 256

extern void keyboard_isr();

extern void isr0();   // ISR0 stub implemented in assembly

extern void isr8();

extern void isr13();

extern void isr14();

extern void isr32();

extern void isr67();


IDTPtr idt_ptr_struct;

InterruptDescription64 idt[IDT_ENTRIES];

void set_idt_gate(my_uint n, my_u64 handler, my_ushort selector, my_char flags) {
    idt[n].offset_low      = handler & 0xFFFF;
    idt[n].selector        = selector;
    idt[n].ist             = 0;
    idt[n].type_attributes = flags;
    idt[n].offset_mid      = (handler >> 16) & 0xFFFF;
    idt[n].offset_high     = (handler >> 32) & 0xFFFFFFFF;
    idt[n].reserved        = 0;
}

void idt_install_keyboard(){
    set_idt_gate(33, (my_u64)keyboard_isr, 0x08, 0x8E);
}

void idt_init(void){
    // *((unsigned short*)0xB8000) = 0x0F41; // Prints a white 'A' on black background
    for(my_int i = 0; i < IDT_ENTRIES; i++){
        idt[i].offset_low = 0;
        idt[i].selector = 0x08;
        idt[i].ist = 0;
        idt[i].type_attributes = 0;
        idt[i].offset_mid = 0;
        idt[i].offset_high = 0;
        idt[i].reserved = 0;
    }

    // 1. THE SANITY CHECK
    // If this fails, my 'InterruptDescription64' struct is likely not packed 
    // or 'reserved' is a 64-bit var instead of a 32-bit var.
    if (sizeof(InterruptDescription64) != 16) {
        my_serial_putstr("CRITICAL ERROR: IDT entry size is not 16 bytes!\n");
        // We halt here because if we continue, we will corrupt memory
        while(1) { asm volatile("hlt"); }
    }

    // *((unsigned short*)0xB8002) = 0x0F42; // Prints a white 'B'

    // 2. INITIALIZE ALL ENTRIES TO 'NOT PRESENT'
    for(my_int i = 0; i < IDT_ENTRIES; i++){
        // We set flags to 0 (Present bit = 0)
        // This ensures a predictable fault if an unmapped interrupt fires.
        set_idt_gate(i, 0, 0, 0); 
    }

    set_idt_gate(0, (my_u64)isr0, 0x08, 0x8E); //Divide by zero
    set_idt_gate(8, (my_u64)isr8, 0x08, 0x8E); 
    set_idt_gate(13, (my_u64)isr13, 0x08, 0x8E);
    set_idt_gate(14, (my_u64)isr14, 0x08, 0x8E);
    set_idt_gate(32, (my_u64)isr32, 0x08, 0x8E); //timer
    set_idt_gate(67, (my_u64)isr67, 0x08, 0b11101110);
    // idt_install_keyboard();

    // Fill IDT pointer for lidt
    idt_ptr_struct.limit = sizeof(idt) - 1;
    idt_ptr_struct.base = (uint64_t)&idt;

    asm volatile("lidt %0" : : "m"(idt_ptr_struct));

    

}
