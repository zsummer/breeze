cd docker
start docker.exe 1
start docker.exe 2
rem set /p wait=
ping 127.0.0.1 -n 2 >nul


cd ..
ping 127.0.0.1 -n 2 >nul