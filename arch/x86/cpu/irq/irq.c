#include "./irq.h"


static void disable_pic(void){
    outb(PIC1_DATA, 0xff);
    outb(PIC2_DATA, 0xff);
}

void irq_init(){
    disable_pic();
}

void irq_enable(){
    asm volatile("sti");
}

void irq_disable(){
    asm volatile("cli");
}