project(xeth)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(libethrpc)
add_subdirectory(libethkey)

#add_subdirectory(libethstealth)

include(${PROJECT_SOURCE_DIR}/cmake/lib.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/app.cmake)

#network webkitwidgets widgets concurrent
#find_package(Qt5 COMPONENTS Core Widgets WebKitWidgets Concurrent REQUIRED)
#find_package(JsonCPP REQUIRED)

#include_directories(
#    ${Qt5Core_INCLUDE_DIRS}
#    ${Qt5Widgets_INCLUDE_DIRS}
#    ${Qt5WebKitWidgets_INCLUDE_DIRS}
#    ${Qt5Concurrent_INCLUDE_DIRS}
#    ${JSONCPP_INCLUDE_DIR}
#    ${PROJECT_SOURCE_DIR}/src
#)

#set(CMAKE_CXX_FLAGS "-fPIC")


#aux_source_directory(src SRC_LIST)

#add_executable(${PROJECT_NAME} ${SRC_LIST})
