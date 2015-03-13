#!/bin/bash

if lsmod | grep "c00clupeaguard" &> /dev/null ; then
    echo "Delete c00clupeaguard"
    sudo rmmod c00clupeaguard
fi
rm -r guardian
tar -xzvf guardian.tar.gz

cd guardian


make x86_64 VERBOSE=y GENTOO=y IFDEV="eno16777728"

echo "installieren? (y|n)"
read TOINSTALL

if [ "$TOINSTALL" == "y" ]
then
    sudo insmod c00clupeaguard.ko
fi
cd ..
