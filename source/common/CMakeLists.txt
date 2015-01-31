cmake_minimum_required(VERSION 3.0)
project(common)


aux_source_directory(./ SRC)
aux_source_directory(./dbhelper HELPER)
aux_source_directory(./tinyxml2 XML)
aux_source_directory(./lua LUA)


SET(LIBRARY_OUTPUT_PATH  ${breeze_SOURCE_DIR}/lib)
add_library(common${LIB_SUFFIX} STATIC ${SRC} ${HELPER} ${XML} ${LUA})

install(TARGETS common${LIB_SUFFIX} 
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
