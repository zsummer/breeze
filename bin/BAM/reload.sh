#!/usr/bin/bash
webPort=`cat ../config.lua |grep "webPort"| awk -F= '{print $2}' |grep -Eo "[0-9]+" `
curl localhost:$webPort/getonline
echo ""
curl localhost:$webPort/reload
echo "3"
sleep 1
echo "2"
sleep 1
echo "1"
sleep 1
curl localhost:$webPort/reload
 


