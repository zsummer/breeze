cd mysql-connector-c-windows

rd /Q /S vs_sln 
md vs_sln
cd vs_sln
cmake ../ -DCMAKE_BUILD_TYPE=Release -A x64 -DCMAKE_GENERATOR_PLATFORM=x64 -DWINDOWS_RUNTIME_MD=1
MSBuild ALL_BUILD.vcxproj /property:Configuration=Release /property:Platform=x64

cmake ../ -DCMAKE_BUILD_TYPE=Debug  -A x64 -DCMAKE_GENERATOR_PLATFORM=x64 -DWINDOWS_RUNTIME_MD=1
MSBuild ALL_BUILD.vcxproj /property:Configuration=Debug /property:Platform=x64

cd ..


ren vs_sln\libmysql\Debug\mysqlclient.pdb mysqlclient_d.pdb
ren vs_sln\libmysql\Debug\mysqlclient.lib mysqlclient_d.lib
xcopy vs_sln\libmysql\Debug\mysqlclient_d.pdb .\lib\  /Y
xcopy vs_sln\libmysql\Debug\mysqlclient_d.lib .\lib\  /Y
xcopy vs_sln\libmysql\Release\mysqlclient.lib .\lib\ /Y

xcopy include\* ..\..\depends_win\include\mysqlclient\  /S /Y /F
xcopy vs_sln\include\*.h ..\..\depends_win\include\mysqlclient\  /S /Y /F
xcopy lib\* ..\..\depends_win\lib\  /S /Y /F

cd ..