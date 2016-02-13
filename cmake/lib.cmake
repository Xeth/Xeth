find_package(Qt5 COMPONENTS Core Widgets WebKitWidgets Concurrent REQUIRED)
find_package(JsonCPP REQUIRED)
find_package(LevelDB REQUIRED)

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIR}
    ${LEVELDB_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}/libethrpc/include
    ${PROJECT_BINARY_DIR}/libethkey/include
    ${PROJECT_SOURCE_DIR}/libethstealth
)

set(CMAKE_CXX_FLAGS "-fPIC")

file(GLOB_RECURSE LIBRARY_SOURCES
    "src/*.cpp"
)


list(REMOVE_ITEM LIBRARY_SOURCES "src/main.cpp")


add_library(xethlib STATIC ${LIBRARY_SOURCES})
add_dependencies(xethlib ethrpc)
add_dependencies(xethlib ethkey)
add_dependencies(xethlib ethstealth)
