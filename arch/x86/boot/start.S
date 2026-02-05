BITS 32

; ------------------------------------------------------------
; Multiboot2 header
; ------------------------------------------------------------
section .multiboot_header
align 8
header_start:
    dd 0xE85250D6                ; Multiboot2 magic
    dd 0                         ; architecture (i386)
    dd header_end - header_start
    dd -(0xE85250D6 + 0 + (header_end - header_start))
    dw 0                         ; end tag
    dw 0
    dd 8
header_end:

; ------------------------------------------------------------
; 32-bit entry point
; ------------------------------------------------------------
section .text
global start
extern kernel_main

start:
    cli

    ; Temporary 32-bit stack
    mov esp, stack_top

    ; Debug: print 'S'
    ; mov dx, 0x3F8
    ; mov al, 'S'
    ; out dx, al

    ; Enable PAE
    mov eax, cr4
    or eax, 1 << 5               ; CR4.PAE
    mov cr4, eax

    ; Loading GDT BEFORE enabling paging
    lgdt [gdt_ptr]
    ;lidt [idt_ptr_struct]

    ; Clear page tables
    mov edi, pml4
    xor eax, eax
    mov ecx, (4096 * 5) / 4
    rep stosd

    ; PML4[0] -> PDPT
    mov eax, pdpt
    or eax, 0b11
    mov dword [pml4], eax

    ; PDPT[0] -> PD
    mov eax, pd
    or eax, 0b11
    mov dword [pdpt], eax

    ; Map 1 GiB with 2 MiB pages
    xor ecx, ecx
.map_pd:
    mov eax, ecx
    shl eax, 21
    or eax, 0b10000011           ; present | write | huge
    mov dword [pd + ecx*8], eax
    mov dword [pd + ecx*8 + 4], 0
    inc ecx
    cmp ecx, 512
    jne .map_pd

    ; Load CR3
    mov eax, pml4
    mov cr3, eax

    ; Enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8               ; EFER.LME
    wrmsr

    ; Enable paging + protected mode
    mov eax, cr0
    or eax, (1 << 31) | (1 << 0) ; PG | PE
    mov cr0, eax

    ; Far jump to long mode
    jmp 0x08:long_mode_start   

; ------------------------------------------------------------
; 64-bit code
; ------------------------------------------------------------
BITS 64
long_mode_start:
    ; Debug: print 'L'
    mov dx, 0x3F8
    mov al, 'L'
    out dx, al

    ; 64-bit stack
    mov rsp, stack_top
    and rsp, -16

    ; Reload segments
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax

    ; Call kernel
    call kernel_main

.hang:
    hlt
    jmp .hang

; ------------------------------------------------------------
; GDT
; ------------------------------------------------------------
section .rodata
align 8
gdt64:
    dq 0
    dq 0x00209A0000000000        ; code (0x08)
    dq 0x0000920000000000        ; data (0x10)

gdt_ptr:
    dw gdt64_end - gdt64 - 1
    dq gdt64
gdt64_end:

extern idt_ptr_struct

; ------------------------------------------------------------
; Page tables + stack
; ------------------------------------------------------------
section .bss
align 4096
pml4: resb 4096
pdpt: resb 4096
pd:   resb 4096

align 16
stack_bottom:
    resb 65536
stack_top:
