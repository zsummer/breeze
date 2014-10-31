#!/bin/bash
for svr in agent auth center  logic  dbagent StressTest; 
do
	ps -ef|grep "\b$svr\b"	
done


