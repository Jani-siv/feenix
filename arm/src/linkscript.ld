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
        KEEP(*(.vectors .vectors.*))
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > rom

    /* .bss section which is used for uninitialized data */
    .bss (NOLOAD) :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > ram

    .data :
    {
        _sdata = .;
        *(.data*);
        _edata = .;
    } > ram AT >rom

    /* stack section */
    .stack (NOLOAD):
    {
        _sstack = .;
        . = ALIGN(8);
        . = . + STACK_SIZE;
        . = ALIGN(8);
        _estack = .;
    } > ram

    _end = . ;
}
