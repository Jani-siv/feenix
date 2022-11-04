.section .vectors, "x"
.global _Reset
_Reset:
    b Reset_Handler
    b Undefined_Instruction
    b Software_Interrupt
    b Prefetch_Abort
    b Data_Abort
    b Reserved
    b IRQ
    b FIQ
.section .text
Reset_Handler:
    ldr r2, str1
    b .
    str1: .word 0xDEADBEEF

Undefined_Instruction:
    nop
Software_Interrupt:
    nop
Prefetch_Abort:
    nop
Data_Abort:
    nop
Reserved:
    nop
IRQ:
    nop
FIQ:
    nop

bl main
