# Install script for directory: /Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local/mysql")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/mysql.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/mysql_com.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/mysql_time.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_list.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_alloc.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/typelib.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_dbug.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/m_string.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_sys.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_xml.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/mysql_embed.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_pthread.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/decimal.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/errmsg.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_global.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_net.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_getopt.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/sslopt-longopts.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_dir.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/sslopt-vars.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/sslopt-case.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/sql_common.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/keycache.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/m_ctype.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_compiler.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/mysql_com_server.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_byteorder.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/byte_order_generic.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/byte_order_generic_x86.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/little_endian.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/big_endian.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/mysql_version.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/my_config.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/mysqld_ername.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/mysqld_error.h"
    "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/sql_state.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mysql" TYPE DIRECTORY FILES "/Users/zhangyawei/Documents/github/breeze/tools/mysql-connector-c-6.1.5-src/include/mysql/" REGEX "/[^/]*\\.h$" REGEX "/psi\\_abi[^/]*$" EXCLUDE)
endif()

