#!/usr/bin/bash
webPort=`cat ../config.lua |grep "webPort"| awk -F= '{print $2}' |grep -Eo "[0-9]+" `
curl 192.168.1.101:$webPort/KickClients?isAll=1

 


