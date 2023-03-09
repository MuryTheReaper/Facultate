#!/bin/bash


D=$1
for F in `find $D -perm -a=w`;do
    file=`ls -l $F | awk -F" " '{print $1}'`
    echo $file $F
    chmod o-w $F
    file=`ls -l $F | awk -F" " '{print $1}'`
    echo $file $F
done
