#!/bin/bash


#if lsmod | grep "c00clupeaguard" &> /dev/null ; then
#    echo "Delete c00clupeaguard"
#    sudo rmmod c00clupeaguard
#fi

cd src

#make x86_64 VERBOSE=y

#sudo insmod c00clupeaguard.ko

tar -zcvf guardian.tar.gz guardian

cd ../


if [ "$EXT" == "y" ]
then
    scp src/guardian.tar.gz gentoobuild:/home/c00clupea/build
    scp src/deploy_local.sh gentoobuild:/home/c00clupea/build
else
    scp src/guardian.tar.gz gentoo1:/home/c00clupea/build
    scp src/deploy_local.sh gentoo1:/home/c00clupea/build
fi



#scp src/guardian/c00clupeaguard.ko :/home/c00clupea/
