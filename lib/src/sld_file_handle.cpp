#include "sld_file_handle.h"
#include <QFileInfo>
#include <QDebug>

SldFileHandle::SldFileHandle()
{

}

long SldFileHandle::sld_doc_type(QString const& fpath){
    QFileInfo fi(fpath);
    QString ext = fi.suffix().toLower();

    if(ext == "sldasm"){
        return swDocumentTypes_e::swDocASSEMBLY;
    }else if(ext == "slddrw"){
        return swDocumentTypes_e::swDocDRAWING;
    }else if(ext == "sldprt"){
        return swDocumentTypes_e::swDocPART;
    }else{
        return swDocumentTypes_e::swDocNONE;
    }
}
