#ifndef LOG_H
#define LOG_H

#include <kernel/types.h>
#include <arch/platform/vga.h>
#include <arch/platform/serial.h>

void kernel_log(const my_uchar* kernel_log_msg);

#endif