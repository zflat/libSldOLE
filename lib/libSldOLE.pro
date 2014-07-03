#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T21:01:19
#
#-------------------------------------------------

QT       -= gui
QT       += testlib

TARGET = libSldOLE
TEMPLATE = lib

DEFINES += LIBSLDOLE_LIBRARY

include($$PWD/libSldOLE.pri)


unix {
    target.path = /usr/lib
    INSTALLS += target
}
