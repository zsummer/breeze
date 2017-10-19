cmake_minimum_required(VERSION 2.8)
project(common)


aux_source_directory(./ SRC)
aux_source_directory(./dbhelper HELPER)
aux_source_directory(./tinyxml2 XML)
aux_source_directory(./lua LUA)
aux_source_directory(./luaextra LUAEXTRA)
aux_source_directory(./md5 MD5)
aux_source_directory(./rvo2 rvo)
aux_source_directory(./aoe aoe)
aux_source_directory(./bcui bcui)


SET(LIBRARY_OUTPUT_PATH  ${breeze_SOURCE_DIR}/lib)
add_library(common${LIB_SUFFIX} STATIC ${SRC} ${HELPER} ${XML} ${LUA} ${LUAEXTRA} ${MD5} ${rvo} ${aoe} ${bcui})

install(TARGETS common${LIB_SUFFIX} 
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
