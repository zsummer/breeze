#!/bin/bash
if [ ! -d zsummerX ]; then
    exit 1
fi
cd zsummerX

sh make.sh $*

cp -r ./depends/* ../../../depends_linux/include/
cp -r ./include/* ../../../depends_linux/include/


cp -r ./lib/*.a ../../../depends_linux/lib/ 
cd ../



