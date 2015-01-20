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
    IPDMWConnectionPtr get_swVault();

    long login();
    long login(const QString & username, const QString & userpwd, const QString & vaultserver, \
               long request_port = 40000, long data_port = 30000);

private:
    IPDMWConnectionPtr swPdmw;
};

#endif // SLD_PDMW_CONTEXT_H
