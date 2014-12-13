# Install script for directory: /root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include

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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/mysql.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/mysql_com.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/mysql_time.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_list.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_alloc.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/typelib.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_dbug.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/m_string.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_sys.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_xml.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/mysql_embed.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_pthread.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/decimal.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/errmsg.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_global.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_net.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_getopt.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/sslopt-longopts.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_dir.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/sslopt-vars.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/sslopt-case.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/sql_common.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/keycache.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/m_ctype.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_compiler.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/mysql_com_server.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_byteorder.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/byte_order_generic.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/byte_order_generic_x86.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/little_endian.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/big_endian.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/mysql_version.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/my_config.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/mysqld_ername.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/mysqld_error.h"
    "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/sql_state.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Development")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mysql" TYPE DIRECTORY FILES "/root/github/mini-breeze/trunk/tools/mysql-connector-c-6.1.5-src/mysql-connector-c-6.1.5-src/include/mysql/" REGEX "/[^/]*\\.h$" REGEX "/psi\\_abi[^/]*$" EXCLUDE)
endif()

