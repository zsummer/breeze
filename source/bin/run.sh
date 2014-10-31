#!/usr/bin/bash
cd auth
./auth 0  2>/dev/null 1>&2 &
./auth 1  2>/dev/null 1>&2 &
ps -ef |grep "\bauth\b" |grep -v "grep"
sleep 2


cd ../logic
./logic 0  2>/dev/null 1>&2 &
ps -ef |grep "\blogic\b" |grep -v "grep"
sleep 2

cd ../center
./center 0  2>/dev/null 1>&2 &
ps -ef |grep "\bcenter\b" | grep -v "grep"
sleep 2


cd ../agent
./agent 0  2>/dev/null 1>&2 &
./agent 1  2>/dev/null 1>&2 &
ps -ef |grep "\bagent\b" | grep -v "grep"

sleep 2
