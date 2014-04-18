QT       += axcontainer

INCLUDEPATH += $$PWD/src \
               $$PWD/include/

SOURCES += $$PWD/src/sld_app_context.cpp \
        $$PWD/src/sld_file_handle.cpp \
        $$PWD/src/sld_component.cpp \
        $$PWD/src/sld_doc.cpp \
        $$PWD/src/sld_model.cpp \

HEADERS += $$PWD/include/sld_app_context.h\
        $$PWD/include/sld_file_handle.h \
        $$PWD/include/sld_component.h \
        $$PWD/include/sld_doc.h \
        $$PWD/include/sld_model.h \
        $$PWD/include/libsldole_global.h \

 # TYPELIBS += $$system(dumpcpp -getfile {83A33D31-27C5-11CE-BFD4-00400513BB57})
 # TYPELIBS += $$system(dumpcpp -getfile {4687F359-55D0-4CD3-B6CF-2EB42C11F989})

