#include <arch/platform/serial.h>
#include <arch/platform/vga.h>

void isr0_handler(void){
    my_serial_putstr("Divide by zero exception!\n");
    my_putstr((const my_uchar*)"Divide by zero exception!\n", 0x0C);

    // Halt CPU safely to prevent repeated faults
    while(1){
        asm volatile("hlt");
    }
}
