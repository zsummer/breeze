
rd /Q /S vs_sln 
md vs_sln
cd vs_sln

cmake ../ -DCMAKE_BUILD_TYPE=Debug  -A x64 -DCMAKE_GENERATOR_PLATFORM=x64
MSBuild breeze.sln /property:Configuration=Debug /property:Platform=x64


rem cmake ../ -DCMAKE_BUILD_TYPE=Release -A x64 -DCMAKE_GENERATOR_PLATFORM=x64 
rem MSBuild breeze.sln /property:Configuration=Release /property:Platform=x64




cd ..