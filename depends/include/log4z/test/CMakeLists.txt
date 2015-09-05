cmake_minimum_required(VERSION 2.6)
project(test)

link_directories(${LOG4Z_LIB_OUT_PATH})

set(EXECUTABLE_OUTPUT_PATH ${LOG4Z_BIN_OUT_PATH})

set(LIBS log4z${LIB_SUFFIX})
if(NOT WIN32)
  set(LIBS ${LIBS} pthread)
endif()

add_executable(fast_test${LIB_SUFFIX} fast_test.cpp)
target_link_libraries(fast_test${LIB_SUFFIX} ${LIBS})

add_executable(advanced_test${LIB_SUFFIX} advanced_test.cpp)
target_link_libraries(advanced_test${LIB_SUFFIX} ${LIBS})

add_executable(stress_test${LIB_SUFFIX} stress_test.cpp)
target_link_libraries(stress_test${LIB_SUFFIX} ${LIBS})



