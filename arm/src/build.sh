#!/bin/bash
arm-none-eabi-as -o startup.o startup.s
arm-none-eabi-ld -T linkscript.ld -o test.elf startup.o
arm-none-eabi-objcopy -O binary test.elf test.bin
