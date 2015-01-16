#ifndef SLD_PDMW_CONTEXT_H
#define SLD_PDMW_CONTEXT_H

#include <QAxObject>
#include <QString>
#include <QDebug>
#include <QStringList>

#include "libsldole_global.h"

class LIBSLDOLESHARED_EXPORT SldPdmwContext
{
public:
    SldPdmwContext();
    ~SldPdmwContext();
    IPDMWConnectionPtr getVault();

private:
    IPDMWConnectionPtr swPdmw;
};

#endif // SLD_PDMW_CONTEXT_H
