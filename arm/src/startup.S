.section .vectors, "x"
.equ STACKINIT,   0x2000
.global _Reset
_Reset:
    .short STACKINIT
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
    bl main
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
