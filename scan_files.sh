#!/bin/sh

make distclean

/opt/checker-276/scan-build ./configure
/opt/checker-276/scan-build make
