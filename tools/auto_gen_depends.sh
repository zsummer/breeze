#!/bin/bash
if [ ! -d zsummerX ]; then
    git clone --depth=1 https://github.com/zsummer/zsummerX
fi
if [ $? -ne 0 ]; then
    echo "git clone depends zsummerX error"
    exit 2
fi
if [ ! -f mysql-connector-c-6.1.11-src.tar.gz ]; then
    wget https://downloads.mysql.com/archives/get/p/19/file/mysql-connector-c-6.1.11-src.tar.gz
fi
if [ ! -d mysql-connector-c-unix ]; then
    tar xzvf mysql-connector-c-6.1.11-src.tar.gz
    mv mysql-connector-c-6.1.11-src mysql-connector-c-unix
fi


if [ ! -d mysql-connector-c-unix ]; then
    echo "tar error"
    exit 3
fi

if [ $? -ne 0 ]; then
  echo "unpacking error"
  exit 4
fi

sh make_zsummerx.sh

if [ $? -ne 0 ]; then
  echo "build zsummerX error"
  exit 5
fi

sh make_mysqlclient.sh
if [ $? -ne 0 ]; then
  echo "build mysqlclient error"
  exit 5
fi
echo "all finish"





