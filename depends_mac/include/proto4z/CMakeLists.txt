cmake_minimum_required(VERSION 2.6)
project(proto4z)

set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "")

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
    add_definitions(-Wall -g -ggdb -O0 )
    set(LIB_SUFFIX "_d")
  else()
    add_definitions(-Wall -O2 -DNDEBUG )
    set(LIB_SUFFIX "")
  endif()
endif(WIN32)
#add_definitions(-D__WITH_TAG)
SET(PROTO4Z_GEN_CODE_PATH ${proto4z_SOURCE_DIR}/test/genCode)
SET(PROTO4Z_BIN_OUT_PATH ${proto4z_SOURCE_DIR}/test/bin)

add_subdirectory(genProto.tools)
add_subdirectory(test)

install(FILES 
${proto4z_SOURCE_DIR}/proto4z.h 
${proto4z_SOURCE_DIR}/dbHelper.h 
${proto4z_SOURCE_DIR}/Proto4z.cs 
${proto4z_SOURCE_DIR}/proto4z.lua 
${proto4z_SOURCE_DIR}/README.md 
${proto4z_SOURCE_DIR}/COPYRIGHT 
DESTINATION include/proto4z)

