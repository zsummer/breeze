cmake_minimum_required(VERSION 2.6)
project(test)

include_directories(../)
aux_source_directory(./ source) 
set(EXECUTABLE_OUTPUT_PATH ./)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_definitions(-Wall -g -ggdb -O0  -D_GLIBCXX_USE_NANOSLEEP)
else()
        add_definitions(-Wall  -O2 -DNDEBUG  -D_GLIBCXX_USE_NANOSLEEP)
endif()

set(CMAKE_CXX_FLAGS -std=c++11)

add_executable(test ${source} )

