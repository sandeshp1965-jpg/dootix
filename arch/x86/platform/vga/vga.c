#include "vga.h"

#define MAX_WIDTH 80
#define MAX_HEIGHT 25

my_int cursor_x = 0;
my_int cursor_y = 0;

volatile my_uchar* vga_memory = (volatile my_uchar*) 0xB8000;

void my_putc(my_uchar character, my_ushort color){
    //volatile my_uchar* vga_memory = (volatile char*) 0xB8000;
    vga_memory[0] = character;
    vga_memory[1] = color;
}
void my_putstr(const my_uchar* str, my_ushort color){
    //volatile my_uchar* vga_memory = (volatile my_uchar*) 0xB8000;
    my_int y = 0;
    my_int x = 0;

    for(my_int i = 0; str[i] != '\0'; i++){
        if(str[i] == '\n'){
            y = y + 1;
            x = 0;
        }
        else{
            my_int offset = (y * MAX_WIDTH + x) * 2;
            vga_memory[offset] = str[i];
            vga_memory[offset + 1] = color;
            x = x+1;

        }

        //line wrap
        if(x >= 80){
            y = y + 1;
            x = 0;
        }
        
        //Screen wrap
        if(y >= 25){
            y = 0;
            x = 0;
        }
    }
}
void clrscr(my_uchar character, my_ushort color){
    
    for(my_int y = 0; y <MAX_HEIGHT; y++){
        for(my_int x = 0; x < MAX_WIDTH; x++){
            my_int offset = (y * MAX_WIDTH + x) * 2;
            vga_memory[offset] = character;
            vga_memory[offset + 1] = (my_uchar)color;

        }
    }


}
