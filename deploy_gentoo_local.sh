#!/bin/bash

./configure --disable-c00clupea --disable-c00swithlink --disable-c00measuretools --enable-writecrap

make -j3

sudo make install
