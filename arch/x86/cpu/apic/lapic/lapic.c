#include "lapic.h"
#include "msr.h"

void lapic_enable_msr(void){
    uint32_t eax, edx;
    rdmsr(IA32_LAPIC_BASE_MSR, &eax, &edx);
    eax |= IA32_LAPIC_ENABLE_BIT;
    wrmsr(IA32_LAPIC_BASE_MSR, eax, edx);
}

void lapic_set_svr(void){
    volatile my_uint* svr = (volatile my_uint*)(LAPIC_BASE_PHYSICAL_ADDRESS + 0xF0);
    *svr = 0x100 | 0xFF;    // Setting bit
}

void lapic_map_mmio(void){
    //We have bee using MMIO mapped since the start as real address is same as that of the virtual address
}

void lapic_set_divide(my_int divide_value){
    *(volatile my_uint*)(LAPIC_BASE_PHYSICAL_ADDRESS + LAPIC_DIVIDE_ADDRESS) = divide_value;
}

void lapic_set_initial_counter(my_int count){
    *(volatile my_uint*)(LAPIC_BASE_PHYSICAL_ADDRESS + INITIAL_COUNT) = count;
}

void lapic_set_timer(my_uint vector, my_int periodic){
    my_uint value = vector;
    value &= ~(1 << 16);          // UNMASK timer
    if(periodic) value |= (1 << 17);    // [periodic mode]
    *(volatile my_uint*)(LAPIC_BASE_PHYSICAL_ADDRESS + LAPIC_LVT_TIMER) = value;
}

void lapic_eoi(void) {
    *(volatile uint32_t*)(LAPIC_BASE_PHYSICAL_ADDRESS + 0xB0) = 0;
}


void lapic_init(){
    lapic_enable_msr();
    lapic_map_mmio();
    lapic_set_svr();
    lapic_set_divide(0b101);
    lapic_set_timer(32,1);
    lapic_set_initial_counter(0x00FFFFFF);
}