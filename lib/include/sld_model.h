#ifndef SLD_MODEL_H
#define SLD_MODEL_H

#include <QString>
#include "libsldole_global.h"
#include "sldcontext.h"

class LIBSLDOLESHARED_EXPORT SldModel
{

public:
    SldModel(SldContext * sld_cont);
    SldModel(SldContext * sld_cont, IModelDoc2** ptr_given_model);
    ~SldModel();

    bool open(QString const& fpath, IModelDoc2Ptr *pRetModel);
    bool close();
    bool save();
    bool change_color(const std::vector<double>& color = std::vector<double>());
    IModelDoc2Ptr iptr();
    QString path_name();

private:
    SldContext * context;
    IModelDoc2Ptr pModel;
    BSTR bstr_config_name;
    BSTR bstr_path;

    void parse_save_err_warns(const long &e,const  long &w);
    void warn(const long &val, const long &sldCONST, const QString & msg);
    void err(const long &val, const long &sldCONST, const QString & msg);
    std::vector<double> rand_color();

};

#endif // SLD_MODEL_H
