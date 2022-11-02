#!/bin/bash
#check mount points
Mountpoint=$(ls /mnt/fat32)
if [ $? != "0" ]; then
    mkdir /mnt/fat32
fi
Mountpoint=$(ls /mnt/ext4)
if [ $? != "0" ]; then
    mkdir /mnt/ext4
fi

#get sizes to mount
sizes=$(fdisk -l $1 | tail -n2 | grep img | xargs | cut -d" " -f2,4,11)

#get size from string
partition1=$(echo $sizes | cut -d " " -f1)
sectors1=$(echo $sizes | cut -d " " -f2)
partition2=$(echo $sizes | cut -d " " -f3)

#calculate correct size
partition1=$(($partition1 * 512))
sectors1=$(($sectors1 * 512))
partition2=$(($partition2 * 512))

#mount filesystem
mount -v -o offset=$partition1,sizelimit=$sectors1 -t vfat $1 /mnt/fat32
mount -v -o offset=$partition2 -t ext4 $1 /mnt/ext4

