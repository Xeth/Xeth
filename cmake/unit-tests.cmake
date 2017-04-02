find_package(Qt5 COMPONENTS Core Widgets WebKitWidgets Concurrent Test REQUIRED)
find_package(JsonCPP REQUIRED)
find_package(Boost COMPONENTS system filesystem thread program_options random regex date_time chrono REQUIRED)
find_package(LevelDB REQUIRED)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)
find_package(GMP)


file(GLOB_RECURSE TEST_SOURCES
    "test/*.cpp"
)

add_definitions(-DBOOST_PP_VARIADICS)
file(COPY ${PROJECT_SOURCE_DIR}/test/data DESTINATION ${PROJECT_BINARY_DIR})

add_executable(xeth-test EXCLUDE_FROM_ALL ${TEST_SOURCES})

target_include_directories(
    xeth-test
    PUBLIC
    ${Boost_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
    ${Qt5Test_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/test
    ${PROJECT_BINARY_DIR}/libethrpc/include
    ${PROJECT_BINARY_DIR}/libethcrypto/include
    ${PROJECT_BINARY_DIR}/libethstealth/include
)


target_link_libraries(xeth-test
    xethlib
    ethstealth
    bitprofile
    ethrpc
    ethcrypto
    ${Qt5Core_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebKitWidgets_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    ${Qt5Test_LIBRARIES}
    ${JSONCPP_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_RANDOM_LIBRARY}
    ${Boost_REGEX_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_CHRONO_LIBRARY}
    ${CRYPTOPP_LIBRARY}
    ${LEVELDB_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

if(GMP_LIBRARIES)
    target_link_libraries(xeth-test ${GMP_LIBRARIES})
endif()

