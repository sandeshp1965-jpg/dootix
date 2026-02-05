#include <kernel/log.h>
#include <kernel/panic.h>
#include <arch/platform/serial.h>
#include <arch/platform/vga.h>

void idt14_handler(void){
    my_serial_putstr("Page Fault");
    my_putstr((const my_uchar*) "Page Fault", 0x0C);

    while(1){
        asm volatile("hlt");
    }
}