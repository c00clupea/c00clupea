#!/bin/sh

sh scan_files.sh

make dist

scp c00clupea-01.tar.gz developc00clupea:/home/c00clupea

tar -czvf htdocs.tar.gz htdocs/

scp htdocs.tar.gz developc00clupea:/home/c00clupea

#ssh cooclupea sh /home/develop/deploy_coo_bsd.sh
