project(xeth)
cmake_minimum_required(VERSION 2.8)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
set(SKIP_LIBRARY_INSTALL TRUE)

include(${PROJECT_SOURCE_DIR}/cmake/modules/OSFlags.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/modules/QRC.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/modules/Test.cmake)

add_subdirectory(libethrpc)
add_subdirectory(libethcrypto)

set(ETHCRYPTO_INCLUDE_DIR "${PROJECT_BINARY_DIR}/libethcrypto/include")
set(ETHCRYPTO_LIBRARY "ethcrypto")
add_subdirectory(libethstealth)

set(ETHRPC_INCLUDE_DIR "${PROJECT_BINARY_DIR}/libethrpc/include")
set(ETHRPC_LIBRARY "ethrpc")
add_subdirectory(libbitprofile)


add_dependencies(bitprofile ethrpc)
add_dependencies(ethstealth ethcrypto)

include(${PROJECT_SOURCE_DIR}/cmake/utils.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/lib.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/app.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/bin.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/unit-tests.cmake)


include(${PROJECT_SOURCE_DIR}/cmake/resources.cmake)


ADD_TEST_TARGET(ethcrypto-tests)
ADD_TEST_TARGET(ethstealth-tests)

#ADD_TEST_TARGET(xeth-tests)
