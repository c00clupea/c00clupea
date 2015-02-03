#!/bin/sh

make distclean

/opt/checker-276/scan-build ./configure --enable-writecrap --disable-c00clupeabox --disable-c00clupea
#/opt/checker-276/scan-build make
