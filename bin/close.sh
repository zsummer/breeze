#!/usr/bin/bash
pID=`ps -ef|grep docker|egrep -v grep|awk '{print$2}'|head -n 1`
if [ "$pID" != "" ]; then
	kill $pID	
fi
