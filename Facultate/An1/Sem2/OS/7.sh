#!/bin/bash

F=$1
S=""
for usr in `cat $F`;do
    S="$S$usr@scs.ubbcluj.ro,"
done

echo ${S%","}
