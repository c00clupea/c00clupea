#!/bin/sh

export CPATH=/usr/local/include
export LIBRARY_PATH=/usr/local/lib
export LD_LIBRARY_PATH=/usr/local/lib

cd /home/develop

rm -r c00clupea-01

tar -xzvf c00clupea-01.tar.gz

tar -xzvf htdocs.tar.gz -C /var/c00clupea/

cd c00clupea-01

./configure --enable-writecrap LDFLAGS="-L/usr/local/lib"

make

make install
