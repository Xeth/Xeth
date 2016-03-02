find_package(Qt5 COMPONENTS Core Widgets WebKit WebKitWidgets Concurrent REQUIRED)



include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/utils
)



add_executable(compiler 
    ${PROJECT_SOURCE_DIR}/utils/compiler.cpp 
    ${PROJECT_SOURCE_DIR}/utils/JavascriptInvoker.cpp 
    ${PROJECT_SOURCE_DIR}/utils/SyncWebView.cpp 
    ${PROJECT_SOURCE_DIR}/utils/UnderscoreCompiler.cpp 
    ${PROJECT_SOURCE_DIR}/utils/js.qrc
)


target_link_libraries(compiler
    ${Qt5WebKitWidgets_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebKit_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    ${Qt5Core_LIBRARIES}
)



add_executable(templatewizard
    ${PROJECT_SOURCE_DIR}/utils/templatewizard.cpp 
    ${PROJECT_SOURCE_DIR}/utils/HtmlMerger.cpp 
    ${PROJECT_SOURCE_DIR}/utils/utils.cpp 
    ${PROJECT_SOURCE_DIR}/utils/SyncWebView.cpp 
)


target_link_libraries(templatewizard
    ${Qt5WebKitWidgets_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5WebKit_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    ${Qt5Core_LIBRARIES}
)



