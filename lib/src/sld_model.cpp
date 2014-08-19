#include <QDir>
#include <QString>
#include <QTime>
#include "sld_model.h"
#include "sld_file_info.h"
#include "smartvars.h"
#include "color_helper.h"

SldModel::~SldModel(){}


SldModel::SldModel(SldContext * sld_cont) :  context(sld_cont), pModel(NULL){}

SldModel::SldModel(SldContext * sld_cont, IModelDoc2** ptr_given_model) \
    : context(sld_cont){

    pModel = (IModelDoc2Ptr)(*ptr_given_model);

    if(NULL == pModel){
        qWarning() << "Null value passed to pModel";
    }
}
IModelDoc2Ptr SldModel::iptr(){
    return pModel;
}

bool SldModel::open(const QString &fpath, IModelDoc2 **pRetModel){

    if(NULL != pModel){
        return false;
    }

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

    context->get_swApp()->OpenDoc6(bstr_path, doctype, open_optns, bstr_config_name, &err, &warn, pRetModel);

    if(NULL == *pRetModel){
        qWarning() << "Could net initialize the model on opening";
        return false;
    }else{
        pModel = *pRetModel;
        return true;
    }
}

bool SldModel::open(QString const& fpath, IModelDoc2Ptr* pRetModel){
    if(NULL != pModel){
        return false;
    }

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

    if(NULL == pModel){
        qWarning() << "Could net initialize the model on opening";
        return false;
    }else{
        pRetModel = (IModelDoc2Ptr*)&pModel;        
        return true;
    }
}

bool SldModel::save(){
    if(NULL == pModel){
        qWarning() << "Model not initialized";
        return false;
    }

    long save_err=0;
    long save_warn=0;
    long save_optns = swSaveAsOptions_e::swSaveAsOptions_Silent\
            | swSaveAsOptions_e::swSaveAsOptions_AvoidRebuildOnSave;
    VARIANT_BOOL bres = false;
    pModel->Save3(save_optns, &save_err, &save_warn, &bres);

    if( !bres ){
        qWarning() << "Save failed";
    }

    parse_save_err_warns(save_err, save_warn);

    bool retval = (bool)bres;
    return retval;
}

bool SldModel::save_as_silent(const QString &fpath, bool as_copy){
    if(NULL == pModel){
        qWarning() << "Model not initialized";
        return false;
    }

    // VARIANT_BOOL bres = false;
    // convert fpath to BSTR
    BSTR bstr_fpath = SysAllocString(fpath.toStdWString().c_str());
    long status;
    VARIANT_BOOL blnvar_as_copy = (as_copy) ? VARIANT_TRUE: VARIANT_FALSE;

    pModel->SaveAsSilent(bstr_fpath, blnvar_as_copy, &status);
    return true;
}

bool SldModel::save_as(const QString &fpath){

    if(NULL == pModel){
        qWarning() << "Model not initialized";
        return false;
    }

    long save_err=0;
    long save_warn=0;
    long save_optns = swSaveAsOptions_e::swSaveAsOptions_Silent\
            | swSaveAsOptions_e::swSaveAsOptions_AvoidRebuildOnSave \
            | swSaveAsOptions_e::swSaveAsOptions_Copy;

    /// Get the ModelDocExtension
    IModelDocExtensionPtr swModelExt;
    HRESULT hres = pModel->get_Extension(&swModelExt);
    if (FAILED(hres)){
        qWarning() << " Could not get the document extension";
        return false;
    }

    ////////////////////////////
    /// Save using the extension

    VARIANT_BOOL bres = false;
    // convert fpath to BSTR
    BSTR bstr_fpath = SysAllocString(fpath.toStdWString().c_str());

    hres = swModelExt->SaveAs(bstr_fpath,\
                       swSaveAsCurrentVersion,\
                       save_optns, \
                       NULL, \
                       &save_err, &save_warn, &bres\
                      );
    if( !bres ){
        qWarning() << "SaveAs failed";
        return false;
    }

    parse_save_err_warns(save_err, save_warn);

    bool retval = (bool)bres;
    return retval;
}

bool SldModel::close(){
    if(NULL == pModel){
        return false;
    }
    BSTR bstr_title;
    pModel->GetTitle(&bstr_title);
    context->get_swApp()->CloseDoc(bstr_title);
    pModel->Release();
    pModel = NULL;
    return true;
}


QString SldModel::path_name(){
    if(NULL == pModel){
        return NULL;
    }
    BSTR pathName;
    HRESULT hres = pModel->GetPathName(&pathName);

    if (FAILED(hres)){
        qWarning() << " Could not get the document path name";
    }else{
        return QString((QChar*)pathName, ::SysStringLen(pathName));
    }

    return NULL;
}

bool SldModel::change_color(const std::vector<double>& color){
    VARIANT_BOOL bret = VARIANT_FALSE;
    HRESULT hres = NOERROR;


    std::vector<double> color_vals = \
            (color.size() >= 3) ? color: ColorHelper::rand_color();

    // SafeArrays example
    // http://help.solidworks.com/2013/English/api/sldworksapi/Get_Spline_Points_Example_CPlusPlus_COM.htm
    // variants array http://www.codeproject.com/Articles/6462/A-simple-class-to-encapsulate-VARIANTs


    ////////////////////////////////////////////////
    // Save a copy of the material properties array

    VARIANT mat_props;
    pModel->get_MaterialPropertyValues(static_cast<VARIANT*>(&mat_props));
    SafeDoubleArray arr_mat_props(mat_props);

    /////////////////////////////////////////////////
    // Overwrite the color in the material properties array

    for(uint i=0; i<=2 && i < arr_mat_props.getSize() ; i++){
        arr_mat_props[i] = color_vals[i];
    }

    //////////////////////////////////////////
    // Remove the existing material properties

    IModelDocExtensionPtr model_extension;
    hres = pModel->get_Extension(&model_extension);
    if(FAILED(hres)){
        qWarning() << "Failed to access IModelDocExtension for the model";
        return false;
    }

    QVariant q_config_count(0);
    long config_count;
    pModel->GetConfigurationCount(&config_count);
    SafeBSTRArray config_names(0,1); // empty array
    hres = model_extension->IRemoveMaterialProperty(\
                swInConfigurationOpts_e::swAllConfiguration,config_count, config_names, &bret);
    if( FAILED(hres) ){
        qWarning()<< "Failed to remove existing material properties for the model";
        // return false;
    }

    ///////////////////////////////////////////////////////////
    // Assign the updated material properties back to the model

    mat_props = static_cast<VARIANT>(arr_mat_props);
    hres = pModel->put_MaterialPropertyValues(mat_props);
    if(FAILED(hres)){
        qWarning()<< "Failed to update existing material properties for the model";
    }

    // rebuild

    hres = pModel->ForceRebuild3(VARIANT_TRUE, &bret);

    return true;
}

void SldModel::parse_save_err_warns(const long &e,const  long &w){
    if( w !=0 ){
        warn(w, swFileSaveWarning_e::swFileSaveWarning_ViewsNeedUpdate, \
             "View needs update");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_RebuildError, \
             "Rebuild error");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_OpenedViewOnly, \
             "Opened view only");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_NeedsRebuild, \
             "Needs rebuild");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_MissingOLEObjects, \
             "Missing OLE Objects");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_MissingOLEObjects, \
             "Missing OLE Objects");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_EdrwingsBadSelection, \
             "Edrawings Bad Selection");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_AnimatorSectionViews, \
             "Animator Section Views");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_AnimatorNeedToSolve, \
             "Animator Need To Solve");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_AnimatorLightEdits, \
             "Animator Light Edits");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_AnimatorFeatureEdits, \
             "Animator Feature Edits");
        warn(w, swFileSaveWarning_e::swFileSaveWarning_AnimatorCameraViews, \
             "Animator Camera Views");
    } // w !=0

    if( e != 0 ){
        err(e, swFileSaveError_e::swFileLockError, \
            "File Lock Error");
        err(e, swFileSaveError_e::swFileNameContainsAtSign, \
            "Name contains at, @, Sign");
        err(e, swFileSaveError_e::swFileNameEmpty, \
            "File Name Empty");
        err(e, swFileSaveError_e::swFileSaveAsBadEDrawingsVersion, \
            "File Save As Bad Edrawings Version");
        err(e, swFileSaveError_e::swFileSaveAsDoNotOverwrite, \
            "Save as do not override existing file");
        err(e, swFileSaveError_e::swFileSaveAsInvalidFileExtension, \
            " Filename extension does not match the SolidWorks document type");
        err(e, swFileSaveError_e::swFileSaveAsNameExceedsMaxPathLength, \
            "Filename cannot exceed 255 characters");
        err(e, swFileSaveError_e::swFileSaveAsNoSelection, \
            " Save the selected bodies in a part document. Valid option for IPartDoc::SaveToFile2; however, not a valid option for IModelDocExtension::SaveAs");
        err(e, swFileSaveError_e::swFileSaveAsNotSupported, \
            "Save As operation is not supported, or was executed is such a way that the resulting file might not be complete, possibly because SolidWorks is hidden; if the error persists after setting SolidWorks to visible and re-attempting the Save As operation, contact SolidWorks API support.");
        err(e, swFileSaveError_e::swFileSaveFormatNotAvailable, \
            "Save As file type is not valid");
        err(e, swFileSaveError_e::swFileSaveWithRebuildError, \
            "Obsolete; see swFileSaveWarning_e");
        err(e, swFileSaveError_e::swGenericSaveError, \
            "Generic save error");
        err(e, swFileSaveError_e::swReadOnlySaveError, \
            "Read only save error");

    } // e != 0
}



void SldModel::warn(const long &val, const long &sldCONST, const QString & msg){
    if( (val & sldCONST) != 0){
        qWarning() << msg;
    }
}


void SldModel::err(const long &val, const long &sldCONST, const QString & msg){
    if( (val & sldCONST) != 0){
      qCritical() << msg;
    }
}
