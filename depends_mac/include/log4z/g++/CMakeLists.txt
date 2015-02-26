cmake_minimum_required(VERSION 2.6)
project(liblog4z)

set(source  ${log4z_SOURCE_DIR}/log4z.cpp )

set(LIBRARY_OUTPUT_PATH ${LOG4Z_LIB_OUT_PATH})

add_library(log4z${LIB_SUFFIX} STATIC ${source})

install(TARGETS log4z${LIB_SUFFIX} 
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
install(FILES ${log4z_SOURCE_DIR}/log4z.h ${log4z_SOURCE_DIR}/COPYRIGHT DESTINATION include/log4z)

