;;kernel.asm

;nasm directive - 32 bit
bits 32
section .text
    ;multiboot spec
    align 4
    dd 0x1BADB002            ;magic
    dd 0x00                  ;flags
    dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

global start
extern nu_che_narod_pognali_nahui	;nu_che_narod_pognali_nahui is defined in the c file

start:
    cli 			                    ;block interrupts
    mov esp, stack_space	            ;set stack pointer
    call nu_che_narod_pognali_nahui
    hlt		 	                    ;halt the CPU

section .bss
resb 8192                           ;8KB for stack
stack_space: