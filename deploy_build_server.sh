#!/bin/bash

make dist

scp c00clupea-01.tar.gz buildserver:/home/c00clupea/repositories/build

tar -czvf htdocs.tar.gz htdocs/

scp htdocs.tar.gz buildserver:/home/c00clupea/repositories/build

