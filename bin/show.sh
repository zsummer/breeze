#!/bin/bash
for svr in docker StressTest; 
do
	ps -ef|grep "\b$svr\b"	
done


