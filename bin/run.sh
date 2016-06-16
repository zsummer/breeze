#!/usr/bin/bash
cd docker
./docker 1   &
./docker 2   &
#valgrind --tool=massif --trace-children=yes --time-unit=B --max-snapshots=100 --pages-as-heap=yes --detailed-freq=1000 --massif-out-file=docker1.massif.out.%p ./docker 1 &
#valgrind --tool=massif --trace-children=yes --time-unit=B --max-snapshots=100 --pages-as-heap=yes --detailed-freq=1000 --massif-out-file=docker2.massif.out.%p ./docker 2 &

#valgrind --tool=callgrind --separate-threads=yes ./docker 1 &
#valgrind --tool=callgrind --separate-threads=yes ./docker 2 &


#valgrind --tool=callgrind  --trace-children=yes ./docker 1 &
#valgrind --tool=callgrind  --trace-children=yes ./docker 2 &


ps -ef |grep "\bdocker\b" |grep -v "grep"
sleep 2


