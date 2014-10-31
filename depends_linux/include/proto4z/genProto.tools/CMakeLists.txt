cmake_minimum_required(VERSION 2.6)
project(genProto)


add_definitions(-Wall  -O0 -g -ggdb  -DNDEBUG -std=c++11 -D_GLIBCXX_USE_NANOSLEEP )

set(EXECUTABLE_OUTPUT_PATH ./)

add_executable(genProto genProto.cpp  log4z.cpp  main.cpp  md5.cpp  tinyxml2.cpp  utility.cpp)

target_link_libraries(genProto pthread rt)


