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

function(PARSE_RESOURCES RESOURCE_FILES DIR QRC PARSER)

    file(GLOB DIR_PATH "resources/${DIR}")
    file(GLOB QRC_PATH "resources/${QRC}.qrc")

    list(REMOVE_ITEM ${RESOURCE_FILES} ${DIR_PATH})
    list(REMOVE_ITEM ${RESOURCE_FILES} ${QRC_PATH})

    file(GLOB_RECURSE FILES "${PROJECT_SOURCE_DIR}/resources/${DIR}/*")

    set(GENERATED_FILES "")

    foreach(FILE_PATH ${FILES})
        string(REPLACE ${DIR_PATH} "" FILE_NAME "${FILE_PATH}")
        set(PARSED_NAME ${PROJECT_BINARY_DIR}/resources/${DIR}${FILE_NAME})
        list(APPEND GENERATED_FILES ${PARSED_NAME})
    endforeach()

    set(OUT_DIR ${PROJECT_BINARY_DIR}/resources/${DIR})
    set(OUT_QRC ${PROJECT_BINARY_DIR}/resources/${QRC}.qrc)
    file(MAKE_DIRECTORY ${OUT_DIR})
    set(PARSED_CPP ${PROJECT_BINARY_DIR}/${DIR}.cxx)
    set_source_files_properties(${GENERATED_FILES} PROPERTIES GENERATED TRUE)
    set_source_files_properties(${PARSED_CPP} PROPERTIES GENERATED TRUE)

    add_custom_target(parse_${DIR}_files COMMAND ${PARSER} ${DIR_PATH} ${OUT_DIR} DEPENDS ${PARSER})
    add_custom_target(parse_${DIR}_qrc COMMAND  ${CMAKE_COMMAND} -E copy ${QRC_PATH} ${CMAKE_BINARY_DIR}/resources DEPENDS parse_${DIR}_files)
    add_custom_target(parse_${DIR} COMMAND ${Qt5Core_RCC_EXECUTABLE} ${rcc_options} -name ${QRC} -o ${PARSED_CPP} ${OUT_QRC} DEPENDS parse_${DIR}_qrc)

endfunction(PARSE_RESOURCES)

file(GLOB RESOURCE_FILES "resources/*")

PARSE_RESOURCES(RESOURCE_FILES template template compiler)
PARSE_RESOURCES(RESOURCE_FILES js js jsmin )
PARSE_RESOURCES(RESOURCE_FILES CSS css cssmin)


#file(GLOB TEMPLATE_DIR "resources/template")
#file(GLOB TEMPLATE_QRC "resources/template.qrc")
#file(GLOB CSS_DIR "resources/CSS")
#file(GLOB CSS_QRC "resources/css.qrc")
#file(GLOB JS_DIR "resources/js")
#file(GLOB JS_QRC "resources/js.qrc")
#file(GLOB HTML_DIR "resources/index.html")
#file(GLOB HTML_QRC "resources/html.qrc")

#list(REMOVE_ITEM RESOURCE_FILES ${TEMPLATE_DIR})
#list(REMOVE_ITEM RESOURCE_FILES ${TEMPLATE_QRC})
#list(REMOVE_ITEM RESOURCE_FILES ${CSS_DIR})
#list(REMOVE_ITEM RESOURCE_FILES ${CSS_QRC})
#list(REMOVE_ITEM RESOURCE_FILES ${JS_DIR})
#list(REMOVE_ITEM RESOURCE_FILES ${JS_QRC})
#list(REMOVE_ITEM RESOURCE_FILES ${HTML_DIR})
#list(REMOVE_ITEM RESOURCE_FILES ${HTML_QRC})

file(COPY ${RESOURCE_FILES} DESTINATION ${PROJECT_BINARY_DIR}/resources)
#file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/resources/template)



#file(GLOB TEMPLATE_FILES "${PROJECT_SOURCE_DIR}/resources/template/*.tpl")
#foreach(TEMPLATE_FILE ${TEMPLATE_FILES})
#    get_filename_component(TEMPLATE_NAME ${TEMPLATE_FILE} NAME_WE)
#    set(COMPILED_TEMPALTE_NAME ${PROJECT_BINARY_DIR}/template/${TEMPLATE_NAME}.tpl)
#    list(APPEND GENERATED_TEMPALTES ${COMPILED_TEMPALTE_NAME})
#endforeach()



#set(COMPILED_TEMPALTES_CPP ${PROJECT_BINARY_DIR}/template.cxx)

#set_source_files_properties(${GENERATED_TEMPALTES} PROPERTIES GENERATED TRUE)
#set_source_files_properties(${COMPILED_TEMPALTES_CPP} PROPERTIES GENERATED TRUE)


#add_custom_target(xeth_compiled_templates COMMAND compiler ${PROJECT_SOURCE_DIR}/resources/template ${PROJECT_BINARY_DIR}/resources/template DEPENDS compiler)
#add_custom_target(xeth_templates_qrc COMMAND  ${CMAKE_COMMAND} -E copy ${TEMPLATE_QRC} ${CMAKE_BINARY_DIR}/resources DEPENDS xeth_compiled_templates)
#add_custom_target(xeth_templates  COMMAND ${Qt5Core_RCC_EXECUTABLE} ${rcc_options} -name template -o ${COMPILED_TEMPALTES_CPP} ${PROJECT_BINARY_DIR}/resources/template.qrc DEPENDS xeth_templates_qrc)


add_executable(xeth ${APP_SOURCES} ${PROJECT_BINARY_DIR}/template.cxx ${PROJECT_BINARY_DIR}/CSS.cxx ${PROJECT_BINARY_DIR}/js.cxx ${PROJECT_BINARY_DIR}/resources/icon.qrc ${PROJECT_BINARY_DIR}/resources/html.qrc)

add_dependencies(xeth parse_template)
add_dependencies(xeth parse_CSS)
add_dependencies(xeth parse_js)



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


