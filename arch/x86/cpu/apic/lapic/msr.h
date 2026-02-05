
#ifndef MSR_H
#define MSR_H

#include <kernel/types.h>

// read a 64-bit MSR
static inline void rdmsr(uint32_t msr, uint32_t* eax, uint32_t* edx) {
    asm volatile("rdmsr"
                 : "=a" (*eax), "=d" (*edx)
                 : "c" (msr));
}

// write a 64-bit MSR
static inline void wrmsr(uint32_t msr, uint32_t eax, uint32_t edx) {
    asm volatile("wrmsr"
                 :
                 : "c" (msr), "a" (eax), "d" (edx));
}

#endif
