#!/bin/bash

nr=0
for F in `find $1|tac`; do
    if [ -f $F ]; then
        if echo $F | grep -q -E ".c$"; then
            lines=`wc -l $F| awk -F" " '{print $1}'`
            if [ $lines -gt 500 ]; then
                nr=`expr $nr + 1`
                if [ $nr -gt 2 ];then
                    break
                fi
                echo $F
            fi
        fi
    fi
done

