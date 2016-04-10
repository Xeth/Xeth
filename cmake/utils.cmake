find_package(Qt5 COMPONENTS Core Widgets WebKit WebKitWidgets Concurrent REQUIRED)

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/utils
)


file(GLOB UTILS_SOURCES ${PROJECT_SOURCE_DIR}/utils/lib/*.cpp)


add_library(utils-lib STATIC ${UTILS_SOURCES})


set(UTILS_LIBRARIES 
    utils-lib
    ${Qt5WebKitWidgets_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebKit_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    ${Qt5Core_LIBRARIES}
)

add_custom_target(utils_js_rcc COMMAND ${Qt5Core_RCC_EXECUTABLE} ${rcc_options} -name utils_js_rcc -o ${PROJECT_BINARY_DIR}/utils_js.cxx ${PROJECT_SOURCE_DIR}/utils/js.qrc)
set_source_files_properties(${PROJECT_BINARY_DIR}/utils_js.cxx PROPERTIES GENERATED TRUE)

add_executable(compiler ${PROJECT_SOURCE_DIR}/utils/compiler.cpp ${PROJECT_BINARY_DIR}/utils_js.cxx)
target_link_libraries(compiler ${UTILS_LIBRARIES})

add_dependencies(compiler utils_js_rcc)

add_executable(jsmin ${PROJECT_SOURCE_DIR}/utils/jsmin.cpp ${PROJECT_BINARY_DIR}/utils_js.cxx)

add_dependencies(jsmin utils_js_rcc)
target_link_libraries(jsmin ${UTILS_LIBRARIES})

add_executable(cssmin ${PROJECT_SOURCE_DIR}/utils/cssmin.cpp)
target_link_libraries(cssmin ${UTILS_LIBRARIES})

find_package(JsonCPP REQUIRED)
find_package(Boost COMPONENTS system filesystem thread program_options random regex date_time chrono REQUIRED)
find_package(LevelDB REQUIRED)
find_package(GMP)
set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)


add_executable(dumpdb ${PROJECT_SOURCE_DIR}/utils/dumpdb.cpp)
target_link_libraries(dumpdb 
    xethlib
    ethstealth
    bitprofile
    ethrpc
    ethcrypto
    ${Qt5WebKitWidgets_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebKit_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    ${Qt5Core_LIBRARIES}
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
    target_link_libraries(dumpdb ${GMP_LIBRARIES})
endif()


add_executable(editor ${PROJECT_SOURCE_DIR}/utils/editor.cpp)
target_link_libraries(editor ${UTILS_LIBRARIES})



