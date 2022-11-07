import os
import subprocess


def ping_local_host():
    retval = os.popen('ping -c 1 127.0.0.1').read()
    for iterator in retval:
        if iterator.find("0%") < len(iterator):
            return True
    return False


def run_os_command(filename):
    getmem = subprocess.Popen("../arm/scripts/memory_layout.sh " + filename, shell=True, stdout=subprocess.PIPE).stdout
    mem = getmem.read()
    val = mem.decode()
    return val


def check_memory_layout_elf_file(filename):
    val = run_os_command(filename)
    val = val.split(",")
    for i in range(0, len(val)):
        val[i].strip(",")
        val[i].strip(" ")
    numval = list(map(int, val))
    max_val = 0
    for iterator in numval:
        if iterator >= max_val:
            max_val = iterator
        else:
            return False
    return True
