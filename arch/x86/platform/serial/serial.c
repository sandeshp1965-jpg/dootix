#include "serial.h"

my_int init_serial(){
    outb(COM1_PORT+1, 0x00); //Disabling all interrupts
    outb(COM1_PORT+3, 0x80); //Enable DLAB
    outb(COM1_PORT+0, 0x03); //Set the divisor to 3 (lo byte) 38400 baud
    outb(COM1_PORT+1, 0x00); //hi byte
    outb(COM1_PORT+3, 0x03); //8 bits, no parity, one stop bit
    outb(COM1_PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1_PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set

    return 0;
}

my_int is_transmit_empty(){
    return inb(COM1_PORT + 5) & 0x20; // 0x20 is the "Empty Transmitter Holding Register" flag
}

void my_serial_putc(my_char a){
    while(is_transmit_empty() == 0);
    outb(COM1_PORT, (my_uchar) a);
}

void my_serial_putstr(const my_char* str){
    for(my_int i = 0; str[i] != '\0'; i++){
        my_serial_putc(str[i]);
    }
}

void my_serial_puthex(uint32_t val) {
    char hex[] = "0123456789ABCDEF";
    my_serial_putstr("0x");

    for (int i = 28; i >= 0; i -= 4) {
        my_serial_putc(hex[(val >> i) & 0xF]);
    }
}
