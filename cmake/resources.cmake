
#copy resources
file(GLOB RESOURCE_FILES "resources/*")
file(COPY ${RESOURCE_FILES} DESTINATION ${PROJECT_BINARY_DIR}/resources)
file(COPY ${PROJECT_SOURCE_DIR}/resources/icon DESTINATION ${PROJECT_BINARY_DIR})

include(cmake/modules/QRC.cmake)

ADD_PARSE_RESOURCES_TARGET(parse_template RESOURCE_FILES ${CMAKE_SOURCE_DIR}/resources/template ${PROJECT_BINARY_DIR}/resources/template tpl compiler)
ADD_PARSE_RESOURCES_TARGET(parse_js RESOURCE_FILES ${CMAKE_SOURCE_DIR}/resources/js ${PROJECT_BINARY_DIR}/resources/js js jsmin)
ADD_PARSE_RESOURCES_TARGET(parse_CSS RESOURCE_FILES ${CMAKE_SOURCE_DIR}/resources/CSS ${PROJECT_BINARY_DIR}/resources/CSS css cssmin)


#GENERATE_QRC(CSS ROOT_PATH ${PROJECT_BINARY_DIR}/resources/ RESOURCES CSS img fonts)
#GENERATE_QRC(js ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES js)
#GENERATE_QRC(html ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES html)
#GENERATE_QRC(icon ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES icon)
#GENERATE_QRC(template ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES template)
#GENERATE_QRC(utils_js ROOT_PATH ${PROJECT_SOURCE_DIR}/utils/vendor RESOURCES utils_js)


#include js




function(INCLUDE_COMPONENT TARGET_NAME CMD HTML_FILE DIR DEPS_FILE DEPENDENCY RPEFIX)
    add_custom_target(${TARGET_NAME} COMMAND ${PROJECT_BINARY_DIR}/editor --dependencies=${DEPS_FILE} --prefix=${PREFIX} ${CMD} ${HTML_FILE} ${DIR} WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/resources DEPENDS ${DEPENDENCY})
endfunction(INCLUDE_COMPONENT)

function(INCLUDE_CSS TARGET_NAME HTML_FILE DIR DEPENDENCY PREFIX)
    INCLUDE_COMPONENT(${TARGET_NAME} --include-css ${HTML_FILE} ${DIR} CSS/dependencies.xml ${DEPENDENCY} ${PREFIX})
endfunction(INCLUDE_CSS)

function(INCLUDE_JS TARGET_NAME HTML_FILE DIR DEPENDENCY PREFIX)
    INCLUDE_COMPONENT(${TARGET_NAME} --include-js ${HTML_FILE} ${DIR} js/dependencies.xml ${DEPENDENCY} ${PREFIX})
endfunction(INCLUDE_JS)

function(INCLUDE_SCRIPTS TARGET HTML_FILE PREFIX)
    INCLUDE_JS(${TARGET}_js_vendor_core ${HTML_FILE} js/vendor/core ${PROJECT_BINARY_DIR}/editor ${PREFIX})
    INCLUDE_JS(${TARGET}_js_vendor_libs ${HTML_FILE} js/vendor/libs ${TARGET}_js_vendor_core ${PREFIX})
    INCLUDE_JS(${TARGET}_js_core ${HTML_FILE} js/core ${TARGET}_js_vendor_libs ${PREFIX})
    INCLUDE_JS(${TARGET}_js_models ${HTML_FILE} js/model ${TARGET}_js_core ${PREFIX})
    INCLUDE_JS(${TARGET}_js_views ${HTML_FILE} js/view ${TARGET}_js_models ${PREFIX})
    add_custom_target(${TARGET} DEPENDS ${TARGET}_js_views)
endfunction(INCLUDE_SCRIPTS)

function(INCLUDE_STYLES TARGET HTML_FILE PREFIX)
    INCLUDE_CSS(${TARGET}_css_vendor ${HTML_FILE} CSS/vendor ${PROJECT_BINARY_DIR}/editor ${PREFIX})
    INCLUDE_CSS(${TARGET}_css_core ${HTML_FILE} CSS/core ${TARGET}_css_vendor ${PREFIX})
    INCLUDE_CSS(${TARGET}_css_style ${HTML_FILE} CSS/style ${TARGET}_css_core ${PREFIX})
    add_custom_target(${TARGET} DEPENDS ${TARGET}_css_style)
endfunction(INCLUDE_STYLES)


INCLUDE_SCRIPTS(include_scripts html/index.html ../)
INCLUDE_STYLES(include_styles html/index.html ../)

INCLUDE_SCRIPTS(test_include_scripts test.html ./)
INCLUDE_JS(test_include_simulators test.html test/simulator test_include_scripts ./)
INCLUDE_STYLES(test_include_styles test.html ./)

add_custom_target(test_include_templates COMMAND ${PROJECT_BINARY_DIR}/editor --merge-templates test.html ${PROJECT_SOURCE_DIR}/resources/template WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/resources DEPENDS editor)
add_dependencies(test_include_templates parse_template)
add_custom_target(test_html DEPENDS test_include_styles test_include_simulators test_include_templates)



#DEFINE_COMPILE_QRC_TARGET(icon)
#DEFINE_COMPILE_QRC_TARGET(js)
#DEFINE_COMPILE_QRC_TARGET(CSS)
#DEFINE_COMPILE_QRC_TARGET(template)
#DEFINE_COMPILE_QRC_TARGET(html)
#DEFINE_COMPILE_QRC_TARGET(utils_js)

ADD_QRC_TARGET(CSS ROOT_PATH ${PROJECT_BINARY_DIR}/resources/ RESOURCES CSS img fonts)
ADD_QRC_TARGET(js ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES js)
ADD_QRC_TARGET(html ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES html)
ADD_QRC_TARGET(icon ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES icon)
ADD_QRC_TARGET(template ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES template)

#add_dependencies(compile_js parse_js)
#add_dependencies(compile_CSS parse_CSS)
#add_dependencies(compile_template parse_template)
#add_dependencies(compile_html include_styles)
#add_dependencies(compile_html include_scripts)





add_custom_target(rcc_files COMMAND ${Qt5Core_RCC_EXECUTABLE} ${rcc_options} -name utils_js_rcc -o ${PROJECT_BINARY_DIR}/utils_js.cxx ${PROJECT_SOURCE_DIR}/utils/js.qrc)

