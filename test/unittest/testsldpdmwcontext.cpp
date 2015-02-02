#include "testsldpdmwcontext.h"
#include "sld_model.h"

TestSldPdmwContext::TestSldPdmwContext(QObject *parent) :
    QObject(parent)
{
}


void TestSldPdmwContext::initTestCase()
{
}

void TestSldPdmwContext::cleanupTestCase()
{
}

void TestSldPdmwContext::test_get_first_doc()
{
    SldContext * context = new SldContext();
    long err = context->vault()->login();
    QVERIFY2(err==0, "Failed to log into the vault");
    HRESULT hr;

    IPDMWDocumentsPtr allDocs;
    hr = context->vault()->get_swVault()->get_Documents(NULL, &allDocs);

    QVERIFY2(!FAILED(hr), "Failed to get connection documents");

    VARIANT varDoc;
    int index =0;
    VARIANT varIndex;
    varIndex.lVal = index;
    varIndex.vt = VT_I4;
    hr = allDocs->get_Item(varIndex, &varDoc);
    QVERIFY2(!FAILED(hr), "Failed to get the first document");
    VariantClear(&varIndex);

    IPDMWDocumentPtr doc = (IPDMWDocumentPtr)varDoc;
    BSTR name;
    hr = doc->get_Name(&name);
    QVERIFY2(!FAILED(hr), "Failed to get the first document's name");
    QString strName = QString((QChar*)name, ::SysStringLen(name));
    qDebug() << strName;
    doc->Release();
    VariantClear(&varDoc);

    BSTR rev = SysAllocString(L"");
    hr = context->vault()->get_swVault()->GetSpecificDocument(name, rev, &doc);
    QVERIFY2(!FAILED(hr), "Failed to get the first document by name");
    BSTR bstrVal;
    hr = doc->get_Revision(&bstrVal);
    QVERIFY2(!FAILED(hr), "Failed to get the first document's number");
    QString strVal = QString((QChar*)bstrVal, ::SysStringLen(bstrVal));
    qDebug() << strVal;
    doc->Release();

    allDocs->Release();
    delete context;
}

void TestSldPdmwContext::test_open_connection()
{ /*
    SldPdmwContext * vault = new SldPdmwContext();
    IPDMWConnectionPtr swVaultPtr = vault->get_swVault();
    QVERIFY2(swVaultPtr != NULL, "Failure");

    long err=0;
    BSTR bstr_username = SysAllocString(L"pdmwadmin");
    BSTR bstr_userpwd = SysAllocString(L"pdmwadmin");
    BSTR bstr_vaultserver = SysAllocString(L"localhost");

    swVaultPtr->Login(bstr_username, bstr_userpwd, bstr_vaultserver, 40000, 30000, &err);
    QVERIFY2(err==0, qPrintable(QString("Login failed. Error: %1").arg(err)));

    delete vault;*/
}

void TestSldPdmwContext::test_login(){
    SldContext * context;
    long err;

    context = new SldContext();
    QVERIFY2(context->get_swVault() != NULL, "The context has a connection to the vault");
    QVERIFY2(context->vault() != NULL, "The context has a connection to the vault");
    err = context->vault()->login();
    QVERIFY2(err==0, qPrintable(QString("Login failed. Error: %1").arg(err)));
    delete context;
/*
    context = new SldContext();
    QVERIFY2(context->get_swVault() != NULL, "The context has a connection to the vault");
    QVERIFY2(context->vault() != NULL, "The context has a connection to the vault");
    QString username = QString("pdmwadmin");
    QString userpwd = QString("pdmwadmin");
    QString vaultaddr = QString("localhost");
    err = context->vault()->login(username, userpwd, vaultaddr, NULL, NULL);
    QVERIFY2(err==0, qPrintable(QString("Login failed. Error: %1").arg(err)));
    delete context;*/
}

void TestSldPdmwContext::test_context(){
    SldContext * context = new SldContext();
    QVERIFY2(context->get_swVault() != NULL, "The context has a connection to the vault");
    QVERIFY2(context->vault() != NULL, "The context has a connection to the vault");

    delete context;
}

