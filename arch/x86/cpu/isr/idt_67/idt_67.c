#include <kernel/log.h>
#include <kernel/panic.h>
#include <arch/platform/serial.h>
#include <arch/platform/vga.h>

void isr67_handler(void){
    const my_uchar* code = (const my_uchar*)"User space for syscalls";
    kernel_log(code);
    // panic_handler(code);
}