#!/usr/bin/bash
cd mini-breeze
./mini-breeze 0  2>/dev/null 1>&2 &
ps -ef |grep "\bmini-breeze\b" |grep -v "grep"
sleep 2


