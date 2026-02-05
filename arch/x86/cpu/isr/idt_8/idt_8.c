#include <kernel/log.h>
#include <kernel/panic.h>
#include <arch/platform/serial.h>
#include <arch/platform/vga.h>


void isr8_handler(void){
    my_uchar* code = (my_uchar*) "Double Fault";
    kernel_log(code);
    panic_handler(code);

}