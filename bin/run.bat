cd cluster
start cluster.exe 1
start cluster.exe 2
rem set /p wait=
ping 127.0.0.1 -n 2 >nul


cd ..
ping 127.0.0.1 -n 2 >nul