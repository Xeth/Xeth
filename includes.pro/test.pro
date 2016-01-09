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
    ../test/AccountScanCriterionTest.hpp \
    ../test/ScanCriteriaTest.hpp \
    ../test/BlockChainSimulator.hpp \
    ../test/ScanProgressTest.hpp \
    ../test/StoreSimulator.hpp \
    ../test/StoreSimulator.ipp \
    ../test/StoreRangeTest.hpp \
    ../test/AddressValidatorTest.hpp


SOURCES += \
    ../test/DataBaseDirectory.cpp\
    ../test/AddressBookStoreTest.cpp\
    ../test/main.cpp \
    ../test/ScanIndexStoreTest.cpp \
    ../test/TransactionStoreTest.cpp \
    ../test/AccountScanCriterionTest.cpp \
    ../test/ScanCriteriaTest.cpp \
    ../test/BlockChainSimulator.cpp \
    ../test/ScanProgressTest.cpp \
    ../test/StoreRangeTest.cpp \
    ../test/AddressValidatorTest.cpp



OBJECTS_DIR = $$OBJECTS_DIR/test
MOC_DIR = $$MOC_DIR/test
