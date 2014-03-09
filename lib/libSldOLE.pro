#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T21:01:19
#
#-------------------------------------------------

QT       -= gui

TARGET = libSldOLE
TEMPLATE = lib

DEFINES += LIBSLDOLE_LIBRARY

SOURCES += $$PWD/src/sld_app_context.cpp

HEADERS += $$PWD/include/sld_app_context.h\
        $$PWD/include/libsldole_global.h

INCLUDEPATH += $$PWD/include/

unix {
    target.path = /usr/lib
    INSTALLS += target
}
