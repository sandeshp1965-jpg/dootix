#include <arch/platform/serial.h>
#include <arch/platform/vga.h>
#include <arch/idt.h>
#include <arch/lapic.h>
// #include "keyboard.h"
#include <arch/irq.h>
#include <kernel/panic.h>

void kernel_main_test() {
    clrscr(' ', 0x07);

    my_serial_putstr("Hello");

    my_putstr((const my_uchar*)"Hello Guys \nWelcome to MyOS\n", 0x0F);

    idt_init();
   // idt_install_keyboard(); 
    // asm volatile("lidt %0" : : "m"(idt_ptr_struct));
    my_putstr((const my_uchar*)"IDT loaded \n", 0x0F);

    //IDT loaded
    my_serial_putstr("Hello lidt");

    lapic_enable_msr();     // MSR bit 11
    my_serial_putstr("enable msr");
    lapic_set_svr();        // enable APIC + spurious vector
    *(volatile my_uint*)(LAPIC_BASE_PHYSICAL_ADDRESS + 0x80) = 0; // TPR = 0
    my_serial_putstr("tpr ok\n");

    my_serial_putstr("set svr\n");
    lapic_set_divide(0b101);
    my_serial_putstr("set divide");
    // *(volatile my_uint*)(LAPIC_BASE_PHYSICAL_ADDRESS + 0x3E0) = 0;
    lapic_set_timer(32, 1); // vector 32, periodic

    lapic_set_initial_counter(0x00FFFFFF);
    my_serial_putstr("counter");

    my_serial_putstr("32");

    irq_init();

    // panic_handler();

    asm volatile("int $67");


    // asm volatile("int $32");

// uint32_t id1 = *(volatile uint32_t*)(LAPIC_BASE_PHYSICAL_ADDRESS + 0x20);
// uint32_t id2 = *(volatile uint32_t*)(LAPIC_BASE_PHYSICAL_ADDRESS + 0x20);

// my_serial_putstr("ID1=");
// my_serial_puthex(id1);
// my_serial_putstr(" ID2=");
// my_serial_puthex(id2);
// my_serial_putstr("\n");

    asm volatile("sti");

    // clrscr(' ', 0x07);
    // asm volatile("int $0");

    //Dividing by zero
    // volatile my_int a = 1;
    // volatile my_int b = 0;
    // volatile my_int c = a/b;

    // my_putstr((const my_uchar*)"Checking divide by 0", 0x0F);

    // asm volatile("int $13");

    //my_serial_putstr("Genral Protection Fault");

    // asm volatile("mov $0xDEAD, %ax; mov %ax, %ds");

    // asm volatile("int $0"); // Divide by zero
    // asm volatile("int $13"); // GP fault

    // volatile uint64_t* pf_addr = (uint64_t*)0xDEADC0DE;
    // volatile uint64_t val = *pf_addr; // triggers #PF

    
    my_serial_putstr("Final Hello");

    my_serial_putstr("Final Hello\n");

    while(1) {
        asm volatile("hlt"); // Wait for the interrupt to wake us up
    }
}