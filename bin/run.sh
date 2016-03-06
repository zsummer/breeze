#!/usr/bin/bash
cd cluster
./cluster 1  2>/dev/null 1>&2 &
./cluster 2  2>/dev/null 1>&2 &
ps -ef |grep "\blogic\b" |grep -v "grep"
sleep 2


