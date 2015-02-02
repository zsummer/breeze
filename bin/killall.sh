#!/bin/bash
set -v on
killall stressTest -w
killall agent -w
killall auth -w
killall center -w
killall logic -w
sleep 2
set -v off

