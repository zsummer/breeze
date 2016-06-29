cd makedb
start /wait makedb.exe
echo "%ERRORLEVEL%"
if %ERRORLEVEL% NEQ 0 goto 1
cd ..


cd docker
start docker.exe 1
start docker.exe 2
cd ..

cd world
start world.exe



if %ERRORLEVEL% NEQ 0 goto 1

:0
echo "start server success. "
exit 0

:1
echo "start server had error. error code is %ERRORLEVEL%,  please check it !!!"
pause
exit 1

