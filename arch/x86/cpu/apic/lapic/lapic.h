#ifndef LAPIC_H
#define LAPIC_H
#define LAPIC_BASE_PHYSICAL_ADDRESS 0xFEE00000
#define IA32_LAPIC_BASE_MSR 0x1B
#define IA32_LAPIC_ENABLE_BIT (1 << 11)
#define LAPIC_DIVIDE_ADDRESS 0x3E0
#define INITIAL_COUNT 0x380
#define LAPIC_LVT_TIMER 0x320


#include <kernel/types.h>

// Steps involved:
// 1. Enable Local APIC in IA32_APIC_BASE MSR
// 2. Map the APIC MMIO page
// 3. Set the SVR enable bit

void lapic_enable_msr(void);    //for wrmsr

void lapic_map_mmio(void);      // for paging, making APIC rgisters access via virtual memory

void lapic_set_svr(void);       // writing SVR

void lapic_set_divide(my_int divide_value);

void lapic_set_initial_counter(my_int count);

void lapic_set_timer(my_uint vector, my_int periodic);

void lapic_eoi();

void lapic_init();

#endif