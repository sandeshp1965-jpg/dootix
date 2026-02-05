#include "log.h"

void kernel_log(const my_uchar* kernel_log_msg){
    my_putstr(kernel_log_msg, 0xBF);
    my_serial_putstr((my_char*)kernel_log_msg);
}