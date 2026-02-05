#include <kernel/log.h>
#include <kernel/panic.h>
#include <arch/platform/serial.h>
#include <arch/platform/vga.h>
#include <arch/lapic.h>
#define LAPIC_EOI_SIGNAL 0xB0

volatile my_u64 ticks = 0;

void isr32_handler(void){

    ticks++;

    if ((ticks % 100) == 0) my_serial_putstr(".");

    *(volatile my_uint*)(LAPIC_BASE_PHYSICAL_ADDRESS + LAPIC_EOI_SIGNAL) = 0;
}