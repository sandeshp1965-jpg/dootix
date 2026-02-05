#include "panic.h"
#include <kernel/log.h>

void panic_handler(const my_uchar* code){
    clrscr(' ', 0x10);

    my_putstr(code, 0x1F);

    asm volatile("cli");
    // kernel_log("Exception occured");

    while(1) {
        asm volatile("hlt"); // Wait for the interrupt to wake us up
    }
}
