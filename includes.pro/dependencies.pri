QMAKE_CXXFLAGS += -I$$_PRO_FILE_PWD_/../src

LIBS += -L"$$_PRO_FILE_PWD_/../build/" -lxeth -lboost_system -lboost_program_options -lboost_filesystem -lboost_thread -lleveldb

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += eth-connector
unix: PKGCONFIG += jsoncpp


TARGETDEPS += $$_PRO_FILE_PWD_/../build/libxeth.a
