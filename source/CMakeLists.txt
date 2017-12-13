cmake_minimum_required(VERSION 2.8)
project(breeze)

#set(GLIBC_FLAG  "-v -static-libgcc -static-libstdc++ -Wl,--no-export-dynamic")
#set(GLIBC_INCLUDE "/home/summer/dependlibs/glibc_static/include")
#set(GLIBC_LIB "/home/summer/dependlibs/glibc_static/lib")
#add_definitions(-DGLIBC_INCLUDEDIR=${GLIBC_INCLUDE} -DGLIBC_LIBRARYDIR=${GLIBC_LIB})
#include_directories(${GLIBC_INCLUDE} )
#link_directories(${GLIBC_LIB})

include_directories(${breeze_SOURCE_DIR}/../depends/include)
if (APPLE)
include_directories(${breeze_SOURCE_DIR}/../depends_mac/include)
include_directories(${breeze_SOURCE_DIR}/../depends_mac/include/mysqlclient)
link_directories(${breeze_SOURCE_DIR}/../depends_mac/lib/)
else()
include_directories(${breeze_SOURCE_DIR}/../depends_linux/include)
include_directories(${breeze_SOURCE_DIR}/../depends_linux/include/mysqlclient)
link_directories(${breeze_SOURCE_DIR}/../depends_linux/lib/)
endif()

include_directories(${breeze_SOURCE_DIR}/../protocol/C++)
include_directories(${breeze_SOURCE_DIR}/common)
include_directories(${breeze_SOURCE_DIR}/common/lua)

link_directories(${breeze_SOURCE_DIR}/lib/)


set(LIB_SUFFIX "")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-Wall -g -ggdb -O0  -D_GLIBCXX_USE_NANOSLEEP -static -Wno-deprecated-declarations -Wno-strict-aliasing)
	set(LIB_SUFFIX "_d")
else()
	add_definitions(-Wall  -O2 -DNDEBUG  -D_GLIBCXX_USE_NANOSLEEP -static -Wno-deprecated-declarations -Wno-strict-aliasing)
	set(LIB_SUFFIX "")
endif()
set(CMAKE_CXX_FLAGS "-std=c++1y -fpermissive")



add_subdirectory(common)
add_subdirectory(makedb)
add_subdirectory(docker)
add_subdirectory(stress)
add_subdirectory(test)
add_subdirectory(world)
add_subdirectory(scene)

