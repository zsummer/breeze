cmake_minimum_required(VERSION 3.0)
project(breeze)


include_directories(/boost/include)
link_directories(/boost/lib)



include_directories(${breeze_SOURCE_DIR}/../depends_linux/include)
include_directories(${breeze_SOURCE_DIR}/../protocol/in/C++)
include_directories(${breeze_SOURCE_DIR}/../protocol/out/C++)
include_directories(${breeze_SOURCE_DIR}/common)

link_directories(${breeze_SOURCE_DIR}/../depends_linux/lib/)
link_directories(${breeze_SOURCE_DIR}/lib/)


set(LIB_SUFFIX "")
if (WIN32)
  if(CMAKE_GENERATOR MATCHES "Win64")
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(LIB_SUFFIX "_win64")
    else()
      set(LIB_SUFFIX "_win64d")
    endif()
  else()
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
      set(LIB_SUFFIX "_win32")
    else()
      set(LIB_SUFFIX "_win32d")
    endif()
  endif()
else(WIN32)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-Wall -g -ggdb -O0 -DNDEBUG -std=c++11 -fpermissive -static -Wno-deprecated-declarations -Wno-strict-aliasing)
    set(LIB_SUFFIX "_d")
  else()
    add_definitions(-Wall -O2 -DNDEBUG -std=c++11 -fpermissive -static -Wno-deprecated-declarations -Wno-strict-aliasing)
    set(LIB_SUFFIX "")
  endif()
endif(WIN32)




add_subdirectory(common)
add_subdirectory(agent)
add_subdirectory(auth)
add_subdirectory(center)
add_subdirectory(logic)
add_subdirectory(stressTest)

