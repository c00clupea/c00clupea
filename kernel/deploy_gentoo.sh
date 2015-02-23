#!/bin/bash

if lsmod | grep "modguardian" &> /dev/null ; then
    echo "Delete guardian_mod"
    sudo rmmod modguardian
fi

make distclean

./configure --enable-c00verbose

make

cd src/guardian

sudo insmod modguardian.ko

cd ../../
