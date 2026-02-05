#include <arch/platform/serial.h>
#include <arch/platform/vga.h>
#include <arch/idt.h>
#include <arch/lapic.h>
// #include "keyboard.h"
#include <arch/irq.h>
#include <kernel/panic.h>

void kernel_main(){
    clrscr(' ', 0x07);

    my_putstr((const my_uchar*)"Hi Guys \nWelcome to MyOS\n", 0x0F);

    idt_init();

    irq_init();

    asm volatile("sti");
}