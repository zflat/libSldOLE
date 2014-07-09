#include <QDir>
#include "sld_model.h"
#include "sld_file_info.h"


SldModel::~SldModel()
{

}

SldModel::SldModel(SldContext * sld_cont)
{
    context = sld_cont;
}

bool SldModel::open(QString const& fpath, IModelDoc2Ptr *pRetModel){
    pModel = NULL;
    if(! QDir(fpath).exists(fpath)){
        return false;
    }

    long err=0;
    long warn=0;
    long open_optns = swOpenDocOptions_e::swOpenDocOptions_Silent;
    long doctype = SldFileInfo::sld_doc_type(fpath);

    bstr_config_name = SysAllocString(L"");
    bstr_path = SysAllocString(fpath.toStdWString().c_str());

    if(doctype == swDocumentTypes_e::swDocNONE){
        return false;
    }

    context->get_swApp()->OpenDoc6(bstr_path, doctype, open_optns, bstr_config_name, &err, &warn, (IModelDoc2**)&pModel);

    if(NULL != pRetModel){
        pRetModel = (IModelDoc2Ptr*)&pModel;
    }

    return true;
}

bool SldModel::close(){
    if(NULL == pModel){
        return false;
    }
    BSTR bstr_title;
    pModel->GetTitle(&bstr_title);
    context->get_swApp()->CloseDoc(bstr_title);
    pModel->Release();
    return true;
}
