#!/bin/sh

sh scan_files.sh

make dist

scp c00clupea-01.tar.gz cooclupea:/home/develop
