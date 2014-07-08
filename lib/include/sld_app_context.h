#ifndef SLD_APP_CONTEXT_H
#define SLD_APP_CONTEXT_H

#include <QAxObject>
#include <QString>
#include <QDebug>

#include "libsldole_global.h"

class LIBSLDOLESHARED_EXPORT SldAppContext
{

public:
    SldAppContext();
    ~SldAppContext();
    ISldWorksPtr getApp();

private:
    ISldWorksPtr swApp;
};

#endif // SLD_APP_CONTEXT_H
