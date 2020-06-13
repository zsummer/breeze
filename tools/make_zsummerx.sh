#!/bin/bash
if [ ! -d zsummerX ]; then
    exit 1
fi
cd zsummerX

sh make.sh $*

cp -r ./depends/* ../../depends/include/
cp -r ./include/* ../../depends/include/

if [ "$(uname)" == "Darwin" ]; then
    cp -r ./lib/*.a ../../depends_mac/lib/ 
else
    cp -r ./lib/*.a ../../depends_linux/lib/ 
fi
cd ../



