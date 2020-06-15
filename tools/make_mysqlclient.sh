#!/bin/bash
if [ ! -d mysql-connector-c-unix ]; then
    echo "no dir" 
    exit 1
fi
cd mysql-connector-c-unix

if [ ! -d build_linux ]; then
    mkdir build_linux
fi
cd build_linux

cmake $* ../ -DCMAKE_BUILD_TYPE=Debug -DWITH_UNIT_TESTS=OFF
make -j2  
cp libmysql/libmysqlclient.a libmysql/libmysqlclient_d.a 
cmake $* ../ -DCMAKE_BUILD_TYPE=Release -DWITH_UNIT_TESTS=OFF
make -j2 

if [ ! -d ../lib ]; then
    mkdir ../lib
fi

cp libmysql/*.a ../lib/  
sys_name=`uname`

if [ "$sys_name" = "Darwin" ]; then
    cp -R ../include/* ../../../depends_mac/include/mysqlclient/ 
    cp -R ./include/*.h ../../../depends_mac/include/mysqlclient/ 
    cp -R ../lib/*.a ../../../depends_mac/lib/ 
else
    cp -R ../include/* ../../../depends_linux/include/mysqlclient/ 
    cp -R ./include/*.h ../../../depends_linux/include/mysqlclient/ 
    cp -R ../lib/*.a ../../../depends_linux/lib/ 
fi

cd ../../



