#!/bin/bash

./configure

make

cd src/guardian

sudo insmod guardian_mod.ko

cd ../../
