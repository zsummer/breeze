cd auth
start auth.exe 0
start auth.exe 1
rem set /p wait=
ping 127.0.0.1 -n 2 >nul

cd ../logic
start logic.exe 0
rem set /p wait=
ping 127.0.0.1 -n 2 >nul

cd ../center
start center.exe 0
rem set /p wait=
ping 127.0.0.1 -n 2 >nul



cd ../agent
start agent.exe 0
start agent.exe 1


cd ..
ping 127.0.0.1 -n 2 >nul