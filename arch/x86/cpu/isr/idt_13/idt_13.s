global isr13
extern isr13_handler

isr13:
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15

    ; sub rsp, 40 ;Create Shadow Space for 64-bit C ABI

   call isr13_handler

    ; add rsp, 40 ;Clean up shadow Space

    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax

    add rsp, 8

   ; call isr13_handler

    iretq
