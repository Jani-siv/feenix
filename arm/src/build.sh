#!/bin/bash
NAME="boot"

arm-none-eabi-gcc -c -nostdlib -nostartfiles -lgcc -o cstart.o cstart.c
arm-none-eabi-ld -T linkscript.ld -o ${NAME}.elf cstart.o
arm-none-eabi-objcopy -O binary ${NAME}.elf ${NAME}.bin
arm-none-eabi-objdump -S ${NAME}.elf > ${NAME}1.list
arm-none-eabi-objdump -d .data ${NAME}.elf
#arm-none-eabi-gcc -c -nostdlib -lgcc -nostartfiles cstart.c -o ${NAME}.o
#arm-none-eabi-ld  -T linkscript.ld  -o ${NAME}.elf ${NAME}.o startup.o
#arm-none-eabi-objcopy -O binary ${NAME}.elf ${NAME}.bin
#arm-none-eabi-objdump -S ${NAME}.elf > ${NAME}.list

