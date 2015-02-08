#!/bin/bash

make dist

scp c00clupea-01.tar.gz cooclupea_loc_deb:/home/c00clupea

scp c00clupea-01.tar.gz cooclupea:/home/develop

tar -czvf htdocs.tar.gz htdocs/

scp htdocs.tar.gz cooclupea:/home/develop

scp htdocs.tar.gz cooclupea_loc_deb:/home/c00clupea
