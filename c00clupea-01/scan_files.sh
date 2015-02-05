#!/bin/sh

make distclean

/opt/checker-276/scan-build ./configure --enable-writecrap
/opt/checker-276/scan-build make
