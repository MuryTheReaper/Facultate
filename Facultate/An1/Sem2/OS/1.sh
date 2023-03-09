#!/bin/bash


for usr in `cat who.fake | awk -F" " '{print $1 }'`; do
    Nr=`cat ps.fake | grep -E "^$usr" -c`
    echo $usr $Nr
done
