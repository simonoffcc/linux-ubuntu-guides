#!/bin/bash

cd linux-6.2.1
make clean > /dev/null
for ((i = 5; i < 10; i++ ))
do
{ time make -j$i > /dev/null ; } 2>&1 | grep real
make clean > /dev/null
done

