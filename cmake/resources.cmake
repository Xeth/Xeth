
file(GLOB RESOURCE_FILES "resources/*")

file(COPY ${RESOURCE_FILES} DESTINATION ${PROJECT_BINARY_DIR}/resources)
file(COPY ${PROJECT_SOURCE_DIR}/resources/icon DESTINATION ${PROJECT_BINARY_DIR})

GENERATE_QRC(css ${PROJECT_BINARY_DIR}/resources/ CSS img fonts)
GENERATE_QRC(js ${PROJECT_BINARY_DIR}/resources js)
GENERATE_QRC(html ${PROJECT_BINARY_DIR}/resources html)
GENERATE_QRC(icon ${PROJECT_BINARY_DIR}/resources icon)
GENERATE_QRC(template ${PROJECT_BINARY_DIR}/resources template)


PARSE_QRC(RESOURCE_FILES template tpl template compiler)
PARSE_QRC(RESOURCE_FILES js js js jsmin )
PARSE_QRC(RESOURCE_FILES CSS css css cssmin)

COMPILE_QRC(icon)

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

add_custom_target(test_include_templates COMMAND ${PROJECT_BINARY_DIR}/editor --merge-templates test.html template WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/resources DEPENDS editor)

add_custom_target(test_html DEPENDS test_include_styles test_include_simulators test_include_templates)


COMPILE_QRC(html)

add_dependencies(compile_html include_styles)
add_dependencies(compile_html include_scripts)





add_custom_target(rcc_files COMMAND ${Qt5Core_RCC_EXECUTABLE} ${rcc_options} -name utils_js_rcc -o ${PROJECT_BINARY_DIR}/utils_js.cxx ${PROJECT_SOURCE_DIR}/utils/js.qrc)

