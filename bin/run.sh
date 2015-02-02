#!/usr/bin/bash
cd logic
./logic 0  2>/dev/null 1>&2 &
ps -ef |grep "\blogic\b" |grep -v "grep"
sleep 2


