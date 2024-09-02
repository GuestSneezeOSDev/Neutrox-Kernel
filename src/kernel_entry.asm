[bits 32]
[extern kernel_main]

section .text
global start

start:
    cli
    cld
    mov ax, 0x10       ; Data segment selector
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000   ; Stack pointer setup

    call kernel_main   ; Call the main kernel function

.halt:
    hlt               ; Halt the CPU
    jmp .halt         ; Infinite loop to halt
