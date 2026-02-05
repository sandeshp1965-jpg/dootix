#include <kernel/log.h>
#include <kernel/panic.h>
#include <arch/platform/serial.h>
#include <arch/platform/vga.h>

void isr13_handler(void){
    // my_putstr((const my_uchar*) "General Protection Fault", 0xDC);
    // my_serial_putstr("General Protection Fault\n");
    const my_uchar* code = "General Protection Fault\n"
    "The PC needs to reboot.\n"
    "Please press the poweroff key to gracefully shutdown and restart";
    // halting so theres no triple fault

    kernel_log("GP Fault");

    panic_handler(code);


    // for(;;);
}