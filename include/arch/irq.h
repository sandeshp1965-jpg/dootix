#ifndef IRQ_H
#define IRQ_H

#include <arch/io.h>
#include <kernel/types.h>

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1    // Command here is the PORT to provide the bit to
#define PIC1_DATA	(PIC1+1)    //Data here is what to provide to the PORT
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

void irq_init();

void irq_enable();

void irq_disable();

#endif