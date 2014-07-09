#ifndef SLD_MODEL_H
#define SLD_MODEL_H

#include <QString>
#include "libsldole_global.h"
#include "sldcontext.h"

class LIBSLDOLESHARED_EXPORT SldModel
{

public:
    SldModel(SldContext * sld_cont);
    ~SldModel();

    bool open(QString const& fpath, IModelDoc2Ptr *pRetModel);
    bool close();

private:
    SldContext * context;
    IModelDoc2Ptr pModel;
    BSTR bstr_config_name;
    BSTR bstr_path;

};

#endif // SLD_MODEL_H
