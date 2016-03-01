project(xeth)
cmake_minimum_required(VERSION 2.8)

add_definitions ("-Wall")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include(${PROJECT_SOURCE_DIR}/cmake/modules/OSFlags.cmake)

add_subdirectory(libethrpc)
add_subdirectory(libethkey)

set(ETHKEY_INCLUDE_DIR "${PROJECT_BINARY_DIR}/libethkey/include")
set(ETHKEY_LIBRARY "ethkey")

add_subdirectory(libethstealth)

add_dependencies(ethstealth ethkey)

include(${PROJECT_SOURCE_DIR}/cmake/utils.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lib.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/app.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/test.cmake)
