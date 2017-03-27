
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




function(INCLUDE_COMPONENT TARGET_NAME CMD DIR DEPS_FILE DEPENDENCY EXTRA)
    add_custom_target(${TARGET_NAME} COMMAND ${PROJECT_BINARY_DIR}/editor ${EXTRA} --dependencies=${DEPS_FILE} --prefix=../ ${CMD} html/index.html ${DIR} WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/resources DEPENDS ${DEPENDENCY})
endfunction(INCLUDE_COMPONENT)

function(INCLUDE_CSS TARGET_NAME DIR DEPENDENCY)
    INCLUDE_COMPONENT(${TARGET_NAME} --include-css ${DIR} CSS/dependencies.xml ${DEPENDENCY} --body=0)
endfunction(INCLUDE_CSS)

function(INCLUDE_JS TARGET_NAME DIR DEPENDENCY)
    INCLUDE_COMPONENT(${TARGET_NAME} --include-js ${DIR} js/dependencies.xml ${DEPENDENCY} --body=0)
endfunction(INCLUDE_JS)

INCLUDE_CSS(css_vendor CSS/vendor ${PROJECT_BINARY_DIR}/editor)
INCLUDE_CSS(css_core CSS/core css_vendor)
INCLUDE_CSS(css_style CSS/style css_core)

INCLUDE_JS(js_vendor_core js/vendor/core ${PROJECT_BINARY_DIR}/editor)
INCLUDE_JS(js_vendor_libs js/vendor/libs js_vendor_core)
INCLUDE_JS(js_core js/core js_vendor_libs)
INCLUDE_JS(js_models js/model js_core)
INCLUDE_JS(js_views js/view js_models)


COMPILE_QRC(html)

add_dependencies(compile_html css_style)
add_dependencies(compile_html js_views)





add_custom_target(rcc_files COMMAND ${Qt5Core_RCC_EXECUTABLE} ${rcc_options} -name utils_js_rcc -o ${PROJECT_BINARY_DIR}/utils_js.cxx ${PROJECT_SOURCE_DIR}/utils/js.qrc)

