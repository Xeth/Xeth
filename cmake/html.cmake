include(cmake/modules/Utils.cmake)

#function(PARSE_INCLUDE_HTML_COMPONENT_ARGUMENTS)

#    set(oneValueArgs TARGET HTML_FILE INCLUDES PREFIX DEPS_FILE)
#    set(multiValueArgs DEPENDS)
#    cmake_parse_arguments(PARSE_HTML "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

#    foreach(VARIABLE_NAME ${oneValueArgs} ${multiValueArgs})
#        set(ARG_NAME PARSE_HTML_${VARIABLE_NAME})
#        set(VARIABLE_VALUE ${${ARG_NAME}})
#        set(${VARIABLE_NAME} ${VARIABLE_VALUE})
#        set(${VARIABLE_NAME} ${VARIABLE_VALUE} PARENT_SCOPE)
#    endforeach()
#    
#endfunction()


function(INCLUDE_HTML_COMPONENT CMD DEFAULT_DEPS_FILE)

#    PARSE_INCLUDE_HTML_COMPONENT_ARGUMENTS(${ARGN})

    PARSE_ARGUMENTS("TARGET;HTML_FILE;PREFIX;DEPS_FILE" "INCLUDES;DEPENDS" ${ARGN})

    if(PREFIX)
        set(PREFIX_ARG "--prefix=${PREFIX}")
    endif()

    if(DEPS_FILE)
        set(DEPS_ARG "--dependencies=${DEPS_FILE}")
    elseif(DEFAULT_DEPS_FILE)
        set(DEPS_ARG "--dependencies=${DEFAULT_DEPS_FILE}")
    endif()

    add_custom_target(${TARGET} COMMAND ${PROJECT_BINARY_DIR}/editor ${DEPS_ARG} ${PREFIX_ARG} ${CMD} ${HTML_FILE} ${INCLUDES} WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/resources)
    if(DEPENDS)
        add_dependencies(${TARGET} ${DEPENDS})
    endif()
    add_dependencies(${TARGET} editor)

endfunction()


function(INCLUDE_CSS)
    INCLUDE_HTML_COMPONENT("--include-css" "CSS/dependencies.xml" ${ARGN})
endfunction()

function(INCLUDE_JS)
    INCLUDE_HTML_COMPONENT("--include-js" "js/dependencies.xml" ${ARGN})
endfunction()


function(INCLUDE_SCRIPTS)

    PARSE_ARGUMENTS("TARGET;HTML_FILE;PREFIX;DEPS_FILE" "INCLUDES;DEPENDS" ${ARGN})
#    PARSE_INCLUDE_HTML_COMPONENT_ARGUMENTS(${ARGN})

    message("---------------------------------- target is " ${TARGET})
    INCLUDE_JS(TARGET ${TARGET}_js_vendor_core HTML_FILE ${HTML_FILE} INCLUDES js/vendor/core PREFIX "${PREFIX}")
    INCLUDE_JS(TARGET ${TARGET}_js_vendor_libs HTML_FILE ${HTML_FILE} INCLUDES js/vendor/libs PREFIX "${PREFIX}" DEPENDS ${TARGET}_js_vendor_core)
    INCLUDE_JS(TARGET ${TARGET}_js_core HTML_FILE ${HTML_FILE} INCLUDES js/core PREFIX "${PREFIX}" DEPENDS ${TARGET}_js_vendor_libs)
    INCLUDE_JS(TARGET ${TARGET}_js_models HTML_FILE ${HTML_FILE} INCLUDES  js/model PREFIX "${PREFIX}" DEPENDS ${TARGET}_js_core)
    INCLUDE_JS(TARGET ${TARGET}_js_views HTML_FILE ${HTML_FILE} INCLUDES js/view PREFIX "${PREFIX}" DEPENDS ${TARGET}_js_models)
    add_custom_target(${TARGET} DEPENDS ${TARGET}_js_views)
endfunction()

function(INCLUDE_STYLES)
    PARSE_ARGUMENTS("TARGET;HTML_FILE;PREFIX;DEPS_FILE" "INCLUDES;DEPENDS" ${ARGN})
#    PARSE_INCLUDE_HTML_COMPONENT_ARGUMENTS(${ARGN})
    INCLUDE_CSS(TARGET ${TARGET}_css_vendor HTML_FILE ${HTML_FILE} INCLUDES CSS/vendor PREFIX "${PREFIX}")
    INCLUDE_CSS(TARGET ${TARGET}_css_core HTML_FILE ${HTML_FILE} INCLUDES CSS/core PREFIX "${PREFIX}" DEPENDS ${TARGET}_css_vendor)
    INCLUDE_CSS(TARGET ${TARGET}_css_style HTML_FILE ${HTML_FILE} INCLUDES CSS/style PREFIX "${PREFIX}" DEPENDS ${TARGET}_css_core)
    add_custom_target(${TARGET} DEPENDS ${TARGET}_css_style)
endfunction()


function(ADD_PARSE_COMMAND)

    message("******************************************************************")
    PARSE_ARGUMENTS("PARSER;TARGET;SOURCE;DESTINATION;EXTENSION" "DEPENDS" ${ARGN})
#    set(oneValueArgs TARGET SOURCE DESTINATION EXTENSION)
#    set(multiValueArgs DEPENDS)
#    cmake_parse_arguments(PARSE "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    foreach(VARIABLE_NAME PARSER TARGET SOURCE DESTINATION EXTENSION DEPENDS)
        message("variable ${VARIABLE_NAME} = ${${VARIABLE_NAME}}")
    endforeach()


    file(GLOB SOURCE ${SOURCE})
    file(GLOB DESTINATION ${DESTINATION})
    if(EXTENSION)
        set(SEARCH_PATTERN  "${SOURCE}/*.${EXTENSION}")
    else()
        set(SEARCH_PATTERN  "${SOURCE}/*")
    endif()

    file(GLOB_RECURSE FILES ${SEARCH_PATTERN})
    set(GENERATED_FILES "")


    foreach(FILE_PATH ${FILES})
        string(REPLACE ${SOURCE} "" FILE_NAME "${FILE_PATH}")
        set(PARSED_FILE ${DESTINATION}${FILE_NAME})
        list(APPEND GENERATED_FILES ${PARSED_FILE})
    endforeach()

    set_source_files_properties(${GENERATED_FILES} PROPERTIES GENERATED TRUE)
    message("command  TARGET ${TARGET} COMMAND ${PARSER} ${SOURCE} ${DESTINATION} DEPENDS ${PARSER}")
    add_custom_target(${TARGET} ALL)
    add_custom_command(TARGET ${TARGET} COMMAND ${PARSER} ${SOURCE} ${DESTINATION} DEPENDS ${PARSER})

    if(DEPENDS)
        add_dependencies(${TARGET} ${DEPENDS})
    endif()

endfunction()







#function(INCLUDE_HTML_COMPONENT TARGET_NAME CMD HTML_FILE DIR DEPS_FILE DEPENDENCY RPEFIX)
#    add_custom_target(${TARGET_NAME} COMMAND ${PROJECT_BINARY_DIR}/editor --dependencies=${DEPS_FILE} --prefix=${PREFIX} ${CMD} ${HTML_FILE} ${DIR} WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/resources DEPENDS ${DEPENDENCY})
#endfunction()

#function(INCLUDE_CSS TARGET_NAME HTML_FILE DIR DEPENDENCY PREFIX)
#    INCLUDE_HTML_COMPONENT(${TARGET_NAME} --include-css ${HTML_FILE} ${DIR} CSS/dependencies.xml ${DEPENDENCY} ${PREFIX})
#endfunction()

#function(INCLUDE_JS TARGET_NAME HTML_FILE DIR DEPENDENCY PREFIX)
#    INCLUDE_HTML_COMPONENT(${TARGET_NAME} --include-js ${HTML_FILE} ${DIR} js/dependencies.xml ${DEPENDENCY} ${PREFIX})
#endfunction()

#function(INCLUDE_SCRIPTS TARGET HTML_FILE PREFIX)
#    INCLUDE_JS(${TARGET}_js_vendor_core ${HTML_FILE} js/vendor/core ${PROJECT_BINARY_DIR}/editor ${PREFIX})
#    INCLUDE_JS(${TARGET}_js_vendor_libs ${HTML_FILE} js/vendor/libs ${TARGET}_js_vendor_core ${PREFIX})
#    INCLUDE_JS(${TARGET}_js_core ${HTML_FILE} js/core ${TARGET}_js_vendor_libs ${PREFIX})
#    INCLUDE_JS(${TARGET}_js_models ${HTML_FILE} js/model ${TARGET}_js_core ${PREFIX})
#    INCLUDE_JS(${TARGET}_js_views ${HTML_FILE} js/view ${TARGET}_js_models ${PREFIX})
#    add_custom_target(${TARGET} DEPENDS ${TARGET}_js_views)
#endfunction()

#function(INCLUDE_STYLES TARGET HTML_FILE PREFIX)
#    INCLUDE_CSS(${TARGET}_css_vendor ${HTML_FILE} CSS/vendor ${PROJECT_BINARY_DIR}/editor ${PREFIX})
#    INCLUDE_CSS(${TARGET}_css_core ${HTML_FILE} CSS/core ${TARGET}_css_vendor ${PREFIX})
#    INCLUDE_CSS(${TARGET}_css_style ${HTML_FILE} CSS/style ${TARGET}_css_core ${PREFIX})
#    add_custom_target(${TARGET} DEPENDS ${TARGET}_css_style)
#endfunction()
