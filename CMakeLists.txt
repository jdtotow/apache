cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME mod_datanoesis)
set(APACHE_PATH "C:/Apache24")
set(MYSQL_PATH "C:/Program Files (x86)/MySQL/MySQL Server 5.7")
set(ORACLE_PATH "C:/Oracle/ODS12cr1Cli/oci")
set(JSONCPP_PATH "C:/json-develop/")
project(${PROJECT_NAME} VERSION 1.0)

set(APACHE_MODULE_PATH "${APACHE_PATH}/modules")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
include_directories(BEFORE "${APACHE_PATH}/include" "${MYSQL_PATH}/include" "${ORACLE_PATH}/include" "C:/soci/include")
link_directories("${APACHE_PATH}/lib" "${MYSQL_PATH}/lib" "${ORACLE_PATH}/lib/msvc" "C:/soci/lib")
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake") 
add_library(
    mod_datanoesis SHARED
    mod_datanoesis.cpp 
    logger.cpp 
)
target_link_libraries(${PROJECT_NAME} libapr-1 libaprutil-1 libhttpd libsoci_core_4_0 libsoci_mysql_4_0 libmysql libsoci_oracle_4_0 oci)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
install (TARGETS mod_datanoesis DESTINATION ${APACHE_MODULE_PATH})