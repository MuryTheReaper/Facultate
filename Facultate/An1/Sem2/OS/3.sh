#!/bin/bash

D=$1
for F in `find $D -type f -name "*.log"`;do
    `sort $F > file`
    `mv file $F`
done
