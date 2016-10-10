cd makedb
start /wait makedb.exe
echo "%ERRORLEVEL%"
if %ERRORLEVEL% NEQ 0 goto 1
cd ..

cd world
start world.exe
cd ..

cd scene
start scene.exe 1
start scene.exe 2
cd ..


cd docker
start docker.exe 1
start docker.exe 2
cd ..




echo "start server success. "



