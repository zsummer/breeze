#!/usr/bin/bash
pID=`ps -ef|grep docker|egrep -v grep|awk '{print$2}'|head -n 1`
if [ "$pID" != "" ]; then
	kill $pID	
fi
killall scene
killall world

while [ 1 -gt 0 ]  
do  
    pids=`ps -ef|grep "docker"| egrep -v "grep" |awk '{print $2}'|xargs`  
    waits=`ps -ef|grep "docker"| egrep -v "grep" |awk '{print "    " $8 " " $9}'`  
    if [ "$pids" = "" ];then  
        echo "all docker exit with success ."  
        break  
    else  
    echo "$waits"  
    fi  
    waitcount=`expr $waitcount + 1`  
    if [ "$waitcount" -gt 10 ]; then  
    forcecount=`expr $waitcount - 10`  
        echo "[warning]looks safe close docker failed. try force kill server [$forcecount]... "  
        kill -9 $pids  
    else  
    echo "please waiting [$waitcount] ...."  
  
    fi  
    sleep 1  
done  
  


