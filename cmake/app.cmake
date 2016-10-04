find_package(Qt5 COMPONENTS Core WebKit WebKitWidgets Concurrent REQUIRED)
find_package(JsonCPP REQUIRED)
#set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system filesystem thread program_options random regex date_time chrono REQUIRED)
find_package(LevelDB REQUIRED)
find_package(GMP)


set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)

file(GLOB_RECURSE WINDOW_SOURCES "src/window/*.cpp")
set(APP_SOURCES src/main.cpp src/Application.cpp ${WINDOW_SOURCES})

#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

if(UNIX AND NOT APPLE)

    if(${Qt5Core_LIBRARIES} VERSION_LESS 5.5.0)
        find_package(AppIndicator)
        find_package(GTK2)
        find_package(LibNotify)

        if(LIBNOTIFY_FOUND)
            message("libnotify support enabled")
            add_definitions(-D__LIBNOTIFY_ENABLED__)
            include_directories(${LIBNOTIFY_INCLUDE_DIR})
        endif()

        if(GTK2_FOUND)
            message("gtk support enabled")
            add_definitions(-D__GTK_ENABLED__)
            include_directories(${GTK2_INCLUDE_DIRS})
        endif()

        if(APPINDICATOR_FOUND AND GTK2_FOUND)
            message("appindicator support enabled")
            add_definitions(-D__UNITY_ENABLED__)
            include_directories(${APPINDICATOR_INCLUDE_DIRS})
        endif()
    endif()

endif()


include_directories(
    ${Boost_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
    ${JSONCPP_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}/libethrpc/include
    ${PROJECT_BINARY_DIR}/libethcrypto/include
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

function(COMPILE_RESOURCE RESOURCE)
    set(RESOURCE_CPP ${PROJECT_BINARY_DIR}/${RESOURCE}.cxx)
    set_source_files_properties(${RESOURCE_CPP} PROPERTIES GENERATED TRUE)
    add_custom_target(compile_${RESOURCE} COMMAND ${Qt5Core_RCC_EXECUTABLE} ${rcc_options} -name ${RESOURCE} -o ${RESOURCE_CPP} ${PROJECT_SOURCE_DIR}/resources/${RESOURCE}.qrc)
endfunction(COMPILE_RESOURCE)

file(GLOB RESOURCE_FILES "resources/*")

PARSE_RESOURCES(RESOURCE_FILES template template compiler)
PARSE_RESOURCES(RESOURCE_FILES js js jsmin )
PARSE_RESOURCES(RESOURCE_FILES CSS css cssmin)
COMPILE_RESOURCE(html)
COMPILE_RESOURCE(icon)

file(COPY ${RESOURCE_FILES} DESTINATION ${PROJECT_BINARY_DIR}/resources)
file(COPY ${PROJECT_SOURCE_DIR}/resources/icon DESTINATION ${PROJECT_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_BINARY_DIR}")

set(APP_SOURCES ${APP_SOURCES} ${PROJECT_BINARY_DIR}/template.cxx ${PROJECT_BINARY_DIR}/CSS.cxx ${PROJECT_BINARY_DIR}/js.cxx ${PROJECT_BINARY_DIR}/icon.cxx  ${PROJECT_BINARY_DIR}/html.cxx)

if(MSVC AND NOT ENABLE_DEBUG)
    add_executable(xeth WIN32 ${APP_SOURCES})
elseif(APPLE)
    add_executable(xeth MACOSX_BUNDLE ${APP_SOURCES})
else()
    add_executable(xeth ${APP_SOURCES})
endif()


add_dependencies(xeth parse_template)
add_dependencies(xeth parse_CSS)
add_dependencies(xeth parse_js)
add_dependencies(xeth compile_html)
add_dependencies(xeth compile_icon)



set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.la;.lib;.so;.dll")


target_link_libraries(xeth
    xethlib
    ethstealth
    bitprofile
    ethrpc
    ethcrypto
    ${Qt5WebKitWidgets_LIBRARIES}
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

if(MSVC AND NOT ENABLE_DEBUG)
    set_target_properties(xeth PROPERTIES  LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
    target_link_libraries(xeth Qt5::WinMain)
endif()

if(GMP_LIBRARIES)
    target_link_libraries(xeth ${GMP_LIBRARIES})
endif()

if(APPINDICATOR_FOUND)
    target_link_libraries(xeth ${APPINDICATOR_LIBRARIES})
endif()

if(LIBNOTIFY_FOUND)
    target_link_libraries(xeth ${LIBNOTIFY_LIBRARIES})
endif()

if(GTK2_FOUND)
    target_link_libraries(xeth ${GTK2_LIBRARIES})
endif()


if(NOT MSVC AND NOT WIN32)
    if(EXISTS ${PROJECT_BINARY_DIR}/vendor)
        install(DIRECTORY ${PROJECT_BINARY_DIR}/vendor DESTINATION /opt/xeth PATTERN * PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
    endif()
    install(DIRECTORY ${PROJECT_BINARY_DIR}/icon DESTINATION /opt/xeth)
    install(TARGETS xeth DESTINATION /opt/xeth)
if(UNIX AND NOT APPLE)
    install(DIRECTORY ${PROJECT_SOURCE_DIR}/shortcuts/usr/share/applications DESTINATION /usr/share )
endif()
else()
    if(EXISTS ${PROJECT_BINARY_DIR}/vendor)
        install(DIRECTORY ${PROJECT_BINARY_DIR}/vendor DESTINATION c:\\Program Files\\XETH PATTERN * PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
    endif()
    install(DIRECTORY ${PROJECT_BINARY_DIR}/icon DESTINATION c:\\Program Files\\XETH)
    install(TARGETS xeth DESTINATION c:\\Program Files\\XETH)
    install(CODE mklink "%userprofile%\Start Menu\Programs\XETH\xeth" "c:\\Program Files\\XETH\xeth.exe")
endif()


