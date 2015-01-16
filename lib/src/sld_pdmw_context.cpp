#include "sld_pdmw_context.h"

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
        swPdmw->Release();
    }
}


IPDMWConnectionPtr SldPdmwContext::getVault()
{
    return swPdmw;
}
