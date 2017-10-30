include(cmake/modules/QRC.cmake)
include(cmake/html.cmake)


#copy resources
file(GLOB RESOURCE_FILES "resources/*")
file(COPY ${RESOURCE_FILES} DESTINATION ${PROJECT_BINARY_DIR}/resources)
file(COPY ${PROJECT_SOURCE_DIR}/resources/icon DESTINATION ${PROJECT_BINARY_DIR})


ADD_PARSE_COMMAND(PARSER compiler TARGET parse_template SOURCE ${CMAKE_SOURCE_DIR}/resources/template DESTINATION ${PROJECT_BINARY_DIR}/resources/template EXTENSION tpl)
ADD_PARSE_COMMAND(PARSER jsmin TARGET parse_js SOURCE ${CMAKE_SOURCE_DIR}/resources/js DESTINATION ${PROJECT_BINARY_DIR}/resources/js EXTENSION js )
ADD_PARSE_COMMAND(PARSER cssmin TARGET parse_CSS SOURCE ${CMAKE_SOURCE_DIR}/resources/CSS DESTINATION ${PROJECT_BINARY_DIR}/resources/CSS EXTENSION css)


#GENERATE_QRC(CSS ROOT_PATH ${PROJECT_BINARY_DIR}/resources/ RESOURCES CSS img fonts)
#GENERATE_QRC(js ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES js)
#GENERATE_QRC(html ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES html)
#GENERATE_QRC(icon ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES icon)
#GENERATE_QRC(template ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES template)
#GENERATE_QRC(utils_js ROOT_PATH ${PROJECT_SOURCE_DIR}/utils/vendor RESOURCES utils_js)


#include js



INCLUDE_SCRIPTS(TARGET include_scripts HTML_FILE html/index.html PREFIX ../ DEPENDS parse_js)
INCLUDE_STYLES(TARGET include_styles HTML_FILE html/index.html PREFIX ../ DEPENDS parse_CSS)



#INCLUDE_SCRIPTS(test_include_scripts test.html ./)
#INCLUDE_JS(test_include_simulators test.html test/simulator test_include_scripts ./)
#INCLUDE_STYLES(test_include_styles test.html ./)

#add_custom_target(test_include_templates COMMAND ${PROJECT_BINARY_DIR}/editor --merge-templates test.html ${PROJECT_SOURCE_DIR}/resources/template WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/resources DEPENDS editor)
#add_dependencies(test_include_templates parse_template)
#add_custom_target(test_html DEPENDS test_include_styles test_include_simulators test_include_templates)



#DEFINE_COMPILE_QRC_TARGET(icon)
#DEFINE_COMPILE_QRC_TARGET(js)
#DEFINE_COMPILE_QRC_TARGET(CSS)
#DEFINE_COMPILE_QRC_TARGET(template)
#DEFINE_COMPILE_QRC_TARGET(html)
#DEFINE_COMPILE_QRC_TARGET(utils_js)

ADD_QRC(TARGET CSS ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES CSS img fonts DEPENDS parse_CSS)
ADD_QRC(TARGET js ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES js DEPENDS parse_js)
ADD_QRC(TARGET icon ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES icon )
ADD_QRC(TARGET template ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES template DEPENDS parse_template)
ADD_QRC(TARGET html ROOT_PATH ${PROJECT_BINARY_DIR}/resources RESOURCES html DEPENDS include_styles include_scripts CSS js icon template)
#add_dependencies(compile_js parse_js)
#add_dependencies(compile_CSS parse_CSS)
#add_dependencies(compile_template parse_template)
#add_dependencies(compile_html include_styles)
#add_dependencies(compile_html include_scripts)





add_custom_target(resources COMMAND ${Qt5Core_RCC_EXECUTABLE} ${rcc_options} -name utils_js_rcc -o ${PROJECT_BINARY_DIR}/utils_js.cxx ${PROJECT_SOURCE_DIR}/utils/js.qrc DEPENDS html )

#add_custom_target(foo_custom DEPENDS foo.ext)
