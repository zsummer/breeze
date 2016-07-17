#! /bin/bash

common=`find ./source/common -maxdepth 1 -type f \( -name "*.cpp" -or -name "*.h" \)  -print0 | xargs -0 cat |grep -v -e ^// -e ^$ -e "^[ ]\*" -e "$\*"| wc -l |awk '{print $1}'`
docker=`find ./source/docker -type f \( -name "*.cpp" -or -name "*.h" \)  -print0 | xargs -0 cat |grep -v -e ^// -e ^$ -e "^[ ]\*" -e "$\*"| wc -l|awk '{print $1}'`
world=`find ./source/world -type f \( -name "*.cpp" -or -name "*.h" \)  -print0 | xargs -0 cat |grep -v -e ^// -e ^$ -e "^[ ]\*" -e "$\*"| wc -l|awk '{print $1}'`
echo "total common=$common,  docker=$docker,  world=$world"
