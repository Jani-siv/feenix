OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
ENTRY(_Reset)
MEMORY
{
  rom      (rx)  : ORIGIN = 0x00000000, LENGTH = 2M
  ram      (rwx) : ORIGIN = 0x20000000, LENGTH = 4M
}

STACK_SIZE = 0x2000;

/* Section Definitions */
SECTIONS
{
    . = 0x0;
    .text :
    {
        . = ALIGN(4);
        KEEP(*(.vectors .vectors.*))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > rom

    /* .bss section which is used for uninitialized data */
    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > ram

    .data :
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data*);
        _edata = .;
    } > ram AT >rom

    /* stack section */
    .stack (NOLOAD):
    {
        _sstack = .;
        . = ALIGN(4);
        . = . + STACK_SIZE;
        . = ALIGN(4);
        _estack = .;
    } > ram

    _end = . ;
}
