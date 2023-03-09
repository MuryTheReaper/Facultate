#!/bin/bash

echo "#:"
for x in $#;do
    echo $x
done

echo "@:"
for x in $@;do
    echo $x
done
