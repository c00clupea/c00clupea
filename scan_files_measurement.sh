#!/bin/sh

make distclean

/opt/checker-276/scan-build ./configure --enable-writecrap --disable-c00clupeabox --disable-c00clupea --disable-c00suname --disable-c00swhoami --disable-c00suptime --disable-c00susleep --disable-c00scat --disable-c00strue --disable-c00sfalse --disable-c00syes --disable-c00sstrings
/opt/checker-276/scan-build make
