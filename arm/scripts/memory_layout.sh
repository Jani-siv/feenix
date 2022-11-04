#!/bin/bash
if  [ $# != 1 ]; then
    echo "Usage: ./memory_layout.sh target.elf"
    exit 1
fi
answer=$(arm-none-eabi-objdump -t $1 | grep ".text" | grep " d " | sed -e's/  */ /g' | cut -d" " -f1 && \
    echo "," && \
    arm-none-eabi-objdump -t $1 | grep ".data" | grep " d " | sed -e's/  */ /g' | cut -d" " -f1 && \
    echo "," && \
    arm-none-eabi-objdump -t $1 | grep ".stack" | grep " d " | sed -e's/  */ /g' | cut -d" " -f1)
echo ${answer} | sed -e's/ *//g'
