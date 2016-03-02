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

add_executable(compiler 
    ${PROJECT_SOURCE_DIR}/utils/compiler.cpp 
    ${PROJECT_SOURCE_DIR}/utils/js.qrc
)


target_link_libraries(compiler
    utils-lib
    ${Qt5WebKitWidgets_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebKit_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    ${Qt5Core_LIBRARIES}
)



add_executable(editor
    ${PROJECT_SOURCE_DIR}/utils/editor.cpp 
)


target_link_libraries(editor
    utils-lib
    ${Qt5WebKitWidgets_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebKit_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    ${Qt5Core_LIBRARIES}
)



