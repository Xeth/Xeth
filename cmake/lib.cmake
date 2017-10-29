find_package(Qt5 COMPONENTS Core Widgets WebKit WebKitWidgets Concurrent REQUIRED)
find_package(JsonCPP REQUIRED)
find_package(LevelDB REQUIRED)
find_package(CryptoPP REQUIRED) 

if(ENABLE_GMP)
    find_package(GMP)
endif()

add_definitions(-DBOOST_PP_VARIADICS)


if(ENABLE_GMP)
    if(GMP_LIBRARIES)
        add_definitions(-D__HAS_GMP__)
    endif()
endif()

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "-fPIC")
endif()

file(GLOB_RECURSE LIBRARY_SOURCES
    "src/*.cpp"
)

file(GLOB_RECURSE MAIN_CPP "src/main.cpp")
file(GLOB_RECURSE APPLICATION_CPP "src/Application.cpp")
file(GLOB_RECURSE WINDOW_CPP "src/window/*.cpp")


list(REMOVE_ITEM LIBRARY_SOURCES ${MAIN_CPP})
list(REMOVE_ITEM LIBRARY_SOURCES ${APPLICATION_CPP})
list(REMOVE_ITEM LIBRARY_SOURCES ${WINDOW_CPP})


add_library(xethlib STATIC ${LIBRARY_SOURCES})
target_include_directories(
    xethlib
    PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKit_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIR}
    ${CRYPTOPP_INCLUDE_DIR}
    ${LEVELDB_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}/libethrpc/include
    ${ETHCRYPTO_INCLUDE_DIRS}
#    ${PROJECT_BINARY_DIR}/libethcrypto/include
    ${PROJECT_BINARY_DIR}/libbitprofile/include
    ${ETHSTEALTH_INCLUDE_DIRS}
#    ${PROJECT_BINARY_DIR}/libethstealth/include
)

add_dependencies(xethlib ethrpc)
add_dependencies(xethlib ethcrypto)
add_dependencies(xethlib ethstealth)
