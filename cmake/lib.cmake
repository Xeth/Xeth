find_package(Qt5 COMPONENTS Core Widgets WebKit WebKitWidgets Concurrent REQUIRED)
find_package(JsonCPP REQUIRED)
find_package(LevelDB REQUIRED)
find_package(GMP)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKit_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIR}
    ${LEVELDB_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}/libethrpc/include
    ${PROJECT_BINARY_DIR}/libethkey/include
    ${PROJECT_SOURCE_DIR}/libethstealth
)

if(GMP_LIBRARIES)
    add_definitions(-D__HAS_GMP__)
endif()

set(CMAKE_CXX_FLAGS "-fPIC")

file(GLOB_RECURSE LIBRARY_SOURCES
    "src/*.cpp"
)

file(GLOB_RECURSE MAIN_CPP "src/main.cpp")
file(GLOB_RECURSE APPLICATION_CPP "src/Application.cpp")
file(GLOB_RECURSE WINDOW_CPP "src/Window.cpp")


list(REMOVE_ITEM LIBRARY_SOURCES ${MAIN_CPP})
list(REMOVE_ITEM LIBRARY_SOURCES ${APPLICATION_CPP})
list(REMOVE_ITEM LIBRARY_SOURCES ${WINDOW_CPP})


add_library(xethlib STATIC ${LIBRARY_SOURCES})
add_dependencies(xethlib ethrpc)
add_dependencies(xethlib ethkey)
add_dependencies(xethlib ethstealth)
