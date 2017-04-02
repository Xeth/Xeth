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
    set(MACOSX_BUNDLE_ICON_FILE xeth.icns)
    set(APP_ICON ${PROJECT_SOURCE_DIR}/resources/icon/xeth.icns)
    set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    add_executable(xeth MACOSX_BUNDLE ${APP_ICON} ${APP_SOURCES})

else()
    add_executable(xeth ${APP_ICON} ${APP_SOURCES})
endif()


add_dependencies(xeth compile_js)
add_dependencies(xeth compile_CSS)
add_dependencies(xeth compile_template)
add_dependencies(xeth compile_html)
add_dependencies(xeth compile_icon)



set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.la;.lib;.so;.dll")

target_include_directories(
    xeth
    PUBLIC
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
        install(DIRECTORY ${PROJECT_BINARY_DIR}/vendor DESTINATION "c:\\Program Files\\XETH" PATTERN * PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
    endif()
    install(DIRECTORY ${PROJECT_BINARY_DIR}/icon DESTINATION "c:\\Program Files\\XETH")
    install(TARGETS xeth DESTINATION "c:\\Program Files\\XETH")
    install(FILES ${Qt5WebKitWidgets_LIBRARIES} ${Qt5WebKit_LIBRARIES} ${Qt5Concurrent_LIBRARIES} ${Qt5Core_LIBRARIES} DESTINATION "c:\\Program Files\\XETH")
    install(CODE mklink "%userprofile%\\Start Menu\\Programs\\XETH\\xeth" "c:\\Program Files\\XETH\\xeth.exe")
endif()


