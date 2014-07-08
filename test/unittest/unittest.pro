#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T21:11:36
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = libSldOLE_unittest
CONFIG   += ordered
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += $$PWD/src \
               $$PWD/include/ \
               $$PWD/

HEADERS += $$PWD/*.h \
    testsldmodel.h \
    testsldappcontext.h

SOURCES += $$PWD/*.cpp \
    testsldmodel.cpp \
    testsldappcontext.cpp
SOURCES += $$PWD/libSldOLE_unittest_main.cpp


DEFINES += SRCDIR=\\\"$$PWD/\\\"


include($$PWD/../../lib/libSldOLE.pri)
