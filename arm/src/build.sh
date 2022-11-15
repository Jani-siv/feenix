#!/bin/bash
NAME="boot"
arm-none-eabi-as -o startup.o startup.S
arm-none-eabi-gcc -c -nostdlib -nostartfiles -lgcc -o cstart.o cstart.c
arm-none-eabi-ld -T linkscript.ld -o ${NAME}.elf startup.o cstart.o --print-map > Mapfile.map
arm-none-eabi-objcopy -O binary ${NAME}.elf ${NAME}.bin
arm-none-eabi-objdump -S ${NAME}.elf > ${NAME}1.list
arm-none-eabi-objdump -d ${NAME}.elf
arm-none-eabi-objcopy -O ihex ${NAME}.elf ${NAME}.hex
