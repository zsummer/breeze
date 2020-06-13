#!/bin/bash
if [ ! -d mysql-connector-c-unix ]; then
    exit 1
fi
cd mysql-connector-c-unix

if [ ! -d build_linux ]; then
    mkdir build_linux
fi
cd build_linux

if [ $# -gt 0 ] && [ $1 = "max" ]; then
    echo "has search max version" 
    if [ -f /usr/bin/g++-8 ]; then 
        cmake -DCMAKE_C_COMPILER=/usr/bin/gcc-8 -DCMAKE_CXX_COMPILER=/usr/bin/g++-8 $* ../ -DCMAKE_BUILD_TYPE=Debug
        make -j2 
        cp libmysql/libmysqlclient.a libmysql/libmysqlclient_d.a 
        cmake -DCMAKE_C_COMPILER=/usr/bin/gcc-8 -DCMAKE_CXX_COMPILER=/usr/bin/g++-8 $* ../ -DCMAKE_BUILD_TYPE=Release
        make -j2 
        
    elif [ -f /usr/bin/g++-6 ]; then 
        cmake -DCMAKE_C_COMPILER=/usr/bin/gcc-6 -DCMAKE_CXX_COMPILER=/usr/bin/g++-6 $* ../ -DCMAKE_BUILD_TYPE=Debug
        make -j2 
        cp libmysql/libmysqlclient.a libmysql/libmysqlclient_d.a 
        cmake -DCMAKE_C_COMPILER=/usr/bin/gcc-6 -DCMAKE_CXX_COMPILER=/usr/bin/g++-6 $* ../ -DCMAKE_BUILD_TYPE=Release
        make -j2 
        
    else
        cmake $* ../ -DCMAKE_BUILD_TYPE=Debug
        make -j2  
        cp libmysql/libmysqlclient.a libmysql/libmysqlclient_d.a 
        cmake $* ../ -DCMAKE_BUILD_TYPE=Release
        make -j2 
    fi
else 
    cmake $* ../ -DCMAKE_BUILD_TYPE=Debug
    make -j2  
    cp libmysql/libmysqlclient.a libmysql/libmysqlclient_d.a 
    cmake $* ../ -DCMAKE_BUILD_TYPE=Release
    make -j2 

fi
if [ ! -d ../lib ]; then
    mkdir ../lib
fi

cp libmysql/*.a ../lib/  

cp -r ../include/* ../../../depends_linux/include/mysqlclient/ 
cp -r libmysql/*.h ../../../depends_linux/include/mysqlclient/ 
cp -r ../lib/*.a ../../../depends_linux/lib/ 
cd ../../



