
file(GLOB RESOURCE_FILES "resources/*")

file(COPY ${RESOURCE_FILES} DESTINATION ${PROJECT_BINARY_DIR}/resources)
file(COPY ${PROJECT_SOURCE_DIR}/resources/icon DESTINATION ${PROJECT_BINARY_DIR})

GENERATE_QRC(css ${PROJECT_BINARY_DIR}/resources/ CSS img fonts)
GENERATE_QRC(js ${PROJECT_BINARY_DIR}/resources js)
GENERATE_QRC(html ${PROJECT_BINARY_DIR}/resources html)
GENERATE_QRC(icon ${PROJECT_BINARY_DIR}/resources icon)
GENERATE_QRC(template ${PROJECT_BINARY_DIR}/resources template)


PARSE_QRC(RESOURCE_FILES template template compiler)
PARSE_QRC(RESOURCE_FILES js js jsmin )
PARSE_QRC(RESOURCE_FILES CSS css cssmin)

COMPILE_QRC(icon)

#include js




function(INCLUDE_COMPONENT TARGET_NAME CMD HTML_FILE DIR DEPS_FILE DEPENDENCY)
    add_custom_target(${TARGET_NAME} COMMAND ${PROJECT_BINARY_DIR}/editor --dependencies=${DEPS_FILE} --prefix=../ ${CMD} ${HTML_FILE} ${DIR} WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/resources DEPENDS ${DEPENDENCY})
endfunction(INCLUDE_COMPONENT)

function(INCLUDE_CSS TARGET_NAME HTML_FILE DIR DEPENDENCY)
    INCLUDE_COMPONENT(${TARGET_NAME} --include-css ${HTML_FILE} ${DIR} CSS/dependencies.xml ${DEPENDENCY} )
endfunction(INCLUDE_CSS)

function(INCLUDE_JS TARGET_NAME HTML_FILE DIR DEPENDENCY)
    INCLUDE_COMPONENT(${TARGET_NAME} --include-js ${HTML_FILE} ${DIR} js/dependencies.xml ${DEPENDENCY})
endfunction(INCLUDE_JS)

function(INCLUDE_SCRIPTS TARGET HTML_FILE)
    INCLUDE_JS(${TARGET}_js_vendor_core ${HTML_FILE} js/vendor/core ${PROJECT_BINARY_DIR}/editor)
    INCLUDE_JS(${TARGET}_js_vendor_libs ${HTML_FILE} js/vendor/libs ${TARGET}_js_vendor_core)
    INCLUDE_JS(${TARGET}_js_core js/core ${HTML_FILE} ${TARGET}_js_vendor_libs)
    INCLUDE_JS(${TARGET}_js_models ${HTML_FILE} js/model ${TARGET}_js_core)
    INCLUDE_JS(${TARGET}_js_views ${HTML_FILE} js/view ${TARGET}_js_models)
    add_custom_target(${TARGET} DEPENDS ${TARGET}_js_views)
endfunction(INCLUDE_SCRIPTS)

function(INCLUDE_STYLES TARGET HTML_FILE)
    INCLUDE_CSS(${TARGET}_css_vendor ${HTML_FILE} CSS/vendor ${PROJECT_BINARY_DIR}/editor)
    INCLUDE_CSS(${TARGET}_css_core ${HTML_FILE} CSS/core ${TARGET}_css_vendor)
    INCLUDE_CSS(${TARGET}_css_style ${HTML_FILE} CSS/style ${TARGET}_css_core)
    add_custom_target(${TARGET} DEPENDS ${TARGET}_css_style)
endfunction(INCLUDE_STYLES)


INCLUDE_SCRIPTS(include_scripts html/index.html)
INCLUDE_STYLES(include_styles html/index.html)

INCLUDE_SCRIPTS(test_base_scripts test/test.html)
INCLUDE_JS(test_scripts test/test.html simulator test_base_scripts)
INCLUDE_STYLES(test_styles test/test.html)

add_custom_target(test_html DEPENDS test_styles test_scripts)


COMPILE_QRC(html)

add_dependencies(compile_html include_styles)
add_dependencies(compile_html include_scripts)





add_custom_target(rcc_files COMMAND ${Qt5Core_RCC_EXECUTABLE} ${rcc_options} -name utils_js_rcc -o ${PROJECT_BINARY_DIR}/utils_js.cxx ${PROJECT_SOURCE_DIR}/utils/js.qrc)

