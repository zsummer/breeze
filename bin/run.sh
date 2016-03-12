#!/usr/bin/bash
cd cluster
./cluster 1   &
./cluster 2   &
ps -ef |grep "\blogic\b" |grep -v "grep"
sleep 2


