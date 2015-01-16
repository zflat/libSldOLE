#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T21:11:36
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = libSldOLE_unittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include($$PWD/../../lib/libSldOLE.pri)


INCLUDEPATH += $$PWD/src \
               $$PWD/include/ \
               $$PWD/

HEADERS += $$PWD/*.h \
    testsldmodel.h \
    testsldappcontext.h \
    testsldpdmwcontext.h \
    testm3dhelper.h

SOURCES += $$PWD/*.cpp \
    testsldmodel.cpp \
    testsldpdmwcontext.cpp \
    testsldappcontext.cpp \
    testm3dhelper.cpp
SOURCES += $$PWD/libSldOLE_unittest_main.cpp


DEFINES += SRCDIR=\\\"$$PWD/\\\"
DEFINES += DATAROOT=\\\"$$PWD/../../../integration/data\\\"
