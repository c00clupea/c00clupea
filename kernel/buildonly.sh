#!/bin/bash

if lsmod | grep "c00clupeaguard" &> /dev/null ; then
    echo "Delete c00clupeaguard"
    sudo rmmod c00clupeaguard
fi

cd src/guardian

make x86_64 VERBOSE=y

cd ../../
