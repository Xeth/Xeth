include($$_PRO_FILE_PWD_/dependencies.pri)
include($$_PRO_FILE_PWD_/destination.pri)


TEMPLATE = app
CONFIG -= console


HEADERS += \
    ../src/Application.hpp \
    ../src/Window.hpp

SOURCES += \
    ../src/Application.cpp \
    ../src/Window.cpp \
    ../src/main.cpp


QT += network webkitwidgets widgets concurrent

RESOURCES = $$_PRO_FILE_PWD_/../resources/xeth.qrc
