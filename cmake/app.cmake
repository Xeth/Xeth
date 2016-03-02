find_package(Qt5 COMPONENTS Core Widgets WebKit WebKitWidgets Concurrent REQUIRED)
find_package(JsonCPP REQUIRED)
find_package(Boost COMPONENTS system filesystem thread program_options random regex date_time chrono REQUIRED)
find_package(LevelDB REQUIRED)
find_package(GMP)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)

set(APP_SOURCES src/main.cpp src/Application.cpp src/window/Window.cpp)


include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}/libethrpc/include
    ${PROJECT_BINARY_DIR}/libethkey/include
    ${PROJECT_BINARY_DIR}/libethstealth/include
)

file(GLOB RESOURCE_FILES "resources/*")
file(GLOB TEMPLATE_DIR "resources/template")
file(GLOB TEMPLATE_QRC "resources/template.qrc")

list(REMOVE_ITEM RESOURCE_FILES ${TEMPLATE_DIR})
list(REMOVE_ITEM RESOURCE_FILES ${TEMPLATE_QRC})

file(COPY ${RESOURCE_FILES} DESTINATION ${PROJECT_BINARY_DIR}/resources)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/resources/template)



file(GLOB TEMPLATE_FILES "${PROJECT_SOURCE_DIR}/resources/template/*.tpl")
foreach(TEMPLATE_FILE ${TEMPLATE_FILES})
    get_filename_component(TEMPLATE_NAME ${TEMPLATE_FILE} NAME_WE)
    set(COMPILED_TEMPALTE_NAME ${PROJECT_BINARY_DIR}/template/${TEMPLATE_NAME}.tpl)
    list(APPEND GENERATED_TEMPALTES ${COMPILED_TEMPALTE_NAME})
endforeach()

set(COMPILED_TEMPALTES_CPP ${PROJECT_BINARY_DIR}/template.cxx)

set_source_files_properties(${GENERATED_TEMPALTES} PROPERTIES GENERATED TRUE)
set_source_files_properties(${COMPILED_TEMPALTES_CPP} PROPERTIES GENERATED TRUE)


add_custom_target(xeth_compiled_templates COMMAND compiler ${PROJECT_SOURCE_DIR}/resources/template ${PROJECT_BINARY_DIR}/resources/template DEPENDS compiler)
add_custom_target(xeth_templates_qrc COMMAND  ${CMAKE_COMMAND} -E copy ${TEMPLATE_QRC} ${CMAKE_BINARY_DIR}/resources DEPENDS xeth_compiled_templates)
add_custom_target(xeth_templates  COMMAND ${Qt5Core_RCC_EXECUTABLE} ${rcc_options} -name template -o ${COMPILED_TEMPALTES_CPP} ${PROJECT_BINARY_DIR}/resources/template.qrc DEPENDS xeth_templates_qrc)


add_executable(xeth ${APP_SOURCES} ${COMPILED_TEMPALTES_CPP} ${PROJECT_BINARY_DIR}/resources/css.qrc ${PROJECT_BINARY_DIR}/resources/js.qrc ${PROJECT_BINARY_DIR}/resources/html.qrc)
add_dependencies(xeth xeth_templates)



set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.lib;.so;.dll")


target_link_libraries(xeth
    xethlib
    ethstealth
    ethrpc
    ethkey
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
    target_link_libraries(xeth ${GMP_LIBRARIES})
endif()


