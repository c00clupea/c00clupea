#!/bin/bash

if lsmod | grep "c00clupeaguard" &> /dev/null ; then
    echo "Delete c00clupeaguard"
    sudo rmmod c00clupeaguard
fi
rm -r guardian
tar -xzvf guardian.tar.gz

cd guardian

echo "use preconfig? (l(local)|e(extern))"
read PRECONF

if [ "$PRECONF" == "l"  ]
then
make x86_64 VERBOSE=y GENTOO=y IFDEV="eno16777728" EXTIP="192.168.101.146" LOCIP="192.168.101.129"
else
make x86_64 VERBOSE=y GENTOO=y IFDEV="enp0s18" EXTIP="192.168.100.119" LOCIP="192.168.100.117"
fi
echo "install? (y|n)"
read TOINSTALL

if [ "$TOINSTALL" == "y" ]
then
    sudo insmod c00clupeaguard.ko
fi
cd ..
