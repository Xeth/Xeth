include($$_PRO_FILE_PWD_/dependencies.pri)
include($$_PRO_FILE_PWD_/destination.pri)

QT       += testlib

QT       -= gui

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    ../test/AddressBookStoreTest.hpp \
    ../test/DataBaseDirectory.hpp \
    ../test/ScanIndexStoreTest.hpp \
    ../test/TransactionStoreTest.hpp \
    ../test/AccountScanCriterionTest.hpp


SOURCES += \
    ../test/DataBaseDirectory.cpp\
    ../test/AddressBookStoreTest.cpp\
    ../test/main.cpp \
    ../test/ScanIndexStoreTest.cpp \
    ../test/TransactionStoreTest.cpp \
    ../test/AccountScanCriterionTest.cpp



OBJECTS_DIR = $$OBJECTS_DIR/test
MOC_DIR = $$MOC_DIR/test
