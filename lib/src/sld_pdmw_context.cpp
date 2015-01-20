#include "sld_pdmw_context.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

SldPdmwContext::SldPdmwContext()
{
    // Exmple at https://support.microsoft.com/kb/216686
    // Get CLSID for our server...
    CLSID clsid;
    HRESULT hr = CLSIDFromProgID(L"PDMWorks.PDMWConnection", &clsid);

    if(FAILED(hr)) {
        qWarning() << "CLSIDFromProgID() failed" << "Error " << 0x10010;
        return;
    }

    // Start server and get IDispatch...
    IDispatch *pPdmwApp;
    hr = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER, IID_IDispatch, (void **)&pPdmwApp);

    if(FAILED(hr)) {
        qWarning() << "CoCreateInstance failed to start pdmw";
        return;
    }

    swPdmw = (IPDMWConnectionPtr)pPdmwApp;
}

SldPdmwContext::~SldPdmwContext()
{
    if(NULL != swPdmw){
        swPdmw->Logout();
        swPdmw->Release();
    }
}

IPDMWConnectionPtr SldPdmwContext::get_swVault()
{
    return swPdmw;
}

long SldPdmwContext::login(const QString & username, const QString & userpwd, const QString & vaultserver,\
                           long request_port, long data_port){

    if(request_port ==0 ){request_port = 40000;}
    if(data_port ==0 ){data_port = 30000;}

    long err=-1;
    if(NULL != swPdmw){
        BSTR bstr_username = SysAllocString(username.toStdWString().c_str());
        BSTR bstr_userpwd = SysAllocString(userpwd.toStdWString().c_str());
        BSTR bstr_vaultserver = SysAllocString(vaultserver.toStdWString().c_str());

        swPdmw->Login(bstr_username, bstr_userpwd, bstr_vaultserver, request_port, data_port, &err);
    }
    return err;
}

/*long SldPdmwContext::login(const QString & username, const QString & userpwd, const QString & vaultserver){
 return login(username, userpwd, vaultserver, (long)40000, 30000);
}*/

long SldPdmwContext::login(){

    QString settingsPathName( QDir::toNativeSeparators(qApp->applicationDirPath()) + QDir::separator() + "config.json");
    QFile settingsFile(settingsPathName);
    if (!settingsFile.open(QIODevice::ReadOnly)) {
       qWarning() << "Couldn't open application settings JSON file at "\
                  << settingsPathName;
       return -1;
    }

    QJsonParseError jerror;
    QByteArray settingsData = settingsFile.readAll();
    QJsonDocument settingsDoc(QJsonDocument::fromJson(settingsData,&jerror));
    if(jerror.error != QJsonParseError::ParseError::NoError){
        qWarning() << "Parse error reading config file: " \
                   << jerror.errorString();
        return -1;
    }

    QJsonObject settings = settingsDoc.object();
    QJsonObject vendorSettings = settings["vendor"].toObject();

    QString username = vendorSettings["pdmw_username"].toString();
    QString userpwd = vendorSettings["pdmw_userpwd"].toString();
    QString server = vendorSettings["pdmw_server"].toString();

    return login(username, userpwd, server);
}
