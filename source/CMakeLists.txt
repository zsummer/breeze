cmake_minimum_required(VERSION 3.0)
project(breeze)

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
include_directories(${breeze_SOURCE_DIR}/common/dbhelper)
include_directories(${breeze_SOURCE_DIR}/common/lua)
include_directories(${breeze_SOURCE_DIR}/common/tinyxml2)
include_directories(${breeze_SOURCE_DIR}/common/md5)

link_directories(${breeze_SOURCE_DIR}/lib/)


set(LIB_SUFFIX "")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-Wall -g -ggdb -O0  -D_GLIBCXX_USE_NANOSLEEP -fpermissive -static -Wno-deprecated-declarations -Wno-strict-aliasing)
	set(LIB_SUFFIX "_d")
else()
	add_definitions(-Wall  -O2 -DNDEBUG  -D_GLIBCXX_USE_NANOSLEEP -fpermissive -static -Wno-deprecated-declarations -Wno-strict-aliasing)
	set(LIB_SUFFIX "")
endif()
set(CMAKE_CXX_FLAGS -std=c++11)

add_subdirectory(common)
add_subdirectory(logic)
add_subdirectory(stress)

