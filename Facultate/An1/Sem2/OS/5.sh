#!/bin/bash

while true;do
    for F in $@;do
        #if ps -ef | grep -E "$F"|grep -v -q -E -e"$0" -e"-E $F"; then
            PID=`ps -ef |grep -E "$F"| grep -v -E -e"$0" |awk -F" " '{print $2}'`
            if [ -n "$PID" ];then
                kill $PID
            fi
    done
    sleep 1
done
