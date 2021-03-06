QT       += axcontainer

INCLUDEPATH += $$PWD/src \
               $$PWD/include/

HEADERS += $$PWD/include/sld_app_context.h\
        $$PWD/include/sld_file_info.h \
        $$PWD/include/sld_component.h \
        $$PWD/include/sld_doc.h \
        $$PWD/include/sld_model.h \
        $$PWD/include/libsldole_global.h \
        $$PWD/include/sldcontext.h \
        $$PWD/include/smartvars.h \
        $$PWD/include/color_helper.h \
        $$PWD/include/m3d_helper.h \
        $$PWD/include/sld_pdmw_context.h

SOURCES += $$PWD/src/sld_app_context.cpp \
        $$PWD/src/sld_file_info.cpp \
        $$PWD/src/sld_component.cpp \
        $$PWD/src/sld_doc.cpp \
        $$PWD/src/sld_model.cpp \
        $$PWD/src/sldcontext.cpp \
        $$PWD/src/color_helper.cpp \
        $$PWD/src/m3d_helper.cpp \
        $$PWD/src/sld_pdmw_context.cpp


# TYPELIBS += $$system(dumpcpp -getfile {83A33D31-27C5-11CE-BFD4-00400513BB57} -compat -nometaobject)
# TYPELIBS += $$system(dumpcpp -getfile {4687F359-55D0-4CD3-B6CF-2EB42C11F989} -compat -n SldConst)

DEFINES += NOMAXMIN
