#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T21:11:36
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = tst_testsldappcontext
CONFIG   += ordered
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/src \
               $$PWD/include/

HEADERS += $$PWD/include/*.h \

SOURCES += $$PWD/src/*.cpp
SOURCES += $$PWD/libSldOLE_unittest_main.cpp


DEFINES += SRCDIR=\\\"$$PWD/\\\"


include($$PWD/../../lib/libSldOLE.pri)
