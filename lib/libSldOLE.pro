#-------------------------------------------------
#
# Project created by QtCreator 2014-03-05T21:01:19
#
#-------------------------------------------------

QT       -= gui

TARGET = libSldOLE
TEMPLATE = lib

DEFINES += LIBSLDOLE_LIBRARY

SOURCES += $$PWD/src/sld_app_context.cpp \
        $$PWD/src/sld_file_handle.cpp \
        $$PWD/src/sld_component.cpp \
        $$PWD/src/sld_doc.cpp \
        $$PWD/src/sld_model.cpp

HEADERS += $$PWD/include/sld_app_context.h\
        $$PWD/include/sld_file_handle.h \
        $$PWD/include/sld_component.h \
        $$PWD/include/sld_doc.h \
        $$PWD/include/sld_model.h \
        $$PWD/include/libsldole_global.h

INCLUDEPATH += $$PWD/include/

unix {
    target.path = /usr/lib
    INSTALLS += target
}
