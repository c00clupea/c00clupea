#!/bin/bash

if lsmod | grep "guardian_mod" &> /dev/null ; then
    echo "Delete guardian_mod"
    sudo rmmod guardian_mod
fi

make distclean

./configure --enable-c00verbose

make

cd src/guardian

sudo insmod guardian_mod.ko

cd ../../
