#!/usr/bin/bash
cd docker
./docker 1   &
./docker 2   &
ps -ef |grep "\bdocker\b" |grep -v "grep"
sleep 2


