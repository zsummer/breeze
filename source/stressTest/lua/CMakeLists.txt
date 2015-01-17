cmake_minimum_required(VERSION 2.6)
project(lpack)

aux_source_directory(./ source) 
set(EXECUTABLE_OUTPUT_PATH ../proto)

add_executable(lpack ${source})

