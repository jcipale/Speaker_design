#!/bin/csh

foreach file (*.sdb)
    cat $file | grep $1 | awk -F';' '{print $1}'
end
