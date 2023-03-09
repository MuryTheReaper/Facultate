#!/bin/bash

D="df.fake"

for name in `awk -F" " 'NR>1 {print $6}' $D`;do
    size=`grep -E "$name$" $D| awk -F" " '{print $3}'`
    used=`grep -E "$name$" $D| awk -F" " '{print $5}'`
    size=${size%"M"}
    used=${used%"%"}
    if [ $size -lt 1024 ] || [ $used -gt 80 ];then
        echo $name #$size $used 
    fi
done

