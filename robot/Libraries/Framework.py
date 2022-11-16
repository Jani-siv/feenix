import os
import subprocess


def ping_local_host():
    retval = os.popen('ping -c 1 127.0.0.1').read()
    for iterator in retval:
        if iterator.find("0%") < len(iterator):
            return True
    return False
