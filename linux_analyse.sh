#!/bin/sh

make distclean

scan-build ./configure
scan-build make
