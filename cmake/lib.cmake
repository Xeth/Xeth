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

file(GLOB LIBRARY_SOURCES
    "src/*.cpp"
    "src/database/*.cpp"
    "src/synchronizer/*.cpp"
    "src/command/wallet/*.cpp"
    "src/command/addressbook/*.cpp"
    "src/command/config/*.cpp"
    "src/facade/*.cpp"
    "src/window/*.cpp"
    "src/process/*.cpp"
    "src/types/*.cpp"
)


list(REMOVE_ITEM LIBRARY_SOURCES "src/main.cpp")


file(GLOB LIBRARY_HEADERS
    "src/*.hpp"
    "src/database/*.hpp"
    "src/synchronizer/*.hpp"
    "src/wallet/*.hpp"
    "src/*.ipp"
    "src/database/*.ipp"
    "src/synchronizer/*.ipp"
    "src/wallet/*.ipp"
    "src/addressbook/*.hpp"
    "src/addressbook/*.ipp"
    "src/config/*.hpp"
    "src/config/*.ipp"
 )

add_library(xethlib STATIC ${LIBRARY_SOURCES})
add_dependencies(xethlib ethrpc)
add_dependencies(xethlib ethkey)
add_dependencies(xethlib ethstealth)
