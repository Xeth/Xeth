TEMPLATE = subdirs
SUBDIRS = includes.pro/lib.pro includes.pro/test.pro includes.pro/app.pro
DESTDIR = $$_PRO_FILE_PWD_/build

QMAKE_POST_LINK = $$_PRO_FILE_PWD_/build/test
