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


}

void TestSldPdmwContext::test_open_connection()
    {
    SldPdmwContext * vault = new SldPdmwContext();
    IPDMWConnectionPtr swVaultPtr = vault->get_swVault();
    QVERIFY2(swVaultPtr != NULL, "Failure");

    long err=0;
    BSTR bstr_username = SysAllocString(L"pdmwadmin");
    BSTR bstr_userpwd = SysAllocString(L"pdmwadmin");
    BSTR bstr_vaultserver = SysAllocString(L"localhost");

    swVaultPtr->Login(bstr_username, bstr_userpwd, bstr_vaultserver, 40000, 30000, &err);
    QVERIFY2(err==0, qPrintable(QString("Login failed. Error: %1").arg(err)));

    delete vault;
}

void TestSldPdmwContext::test_login(){
    SldContext * context;
    long err;

    context = new SldContext();
    QVERIFY2(context->get_swVault() != NULL, "The context has a connection to the vault");
    QVERIFY2(context->vault() != NULL, "The context has a connection to the vault");
    QVERIFY2(context->get_swVault() != NULL, "The context has a connection to the vault");
    QVERIFY2(context->vault() != NULL, "The context has a connection to the vault");
    err = context->vault()->login();
    QVERIFY2(err==0, qPrintable(QString("Login failed. Error: %1").arg(err)));
    delete context;

    context = new SldContext();
    QString username = QString("pdmwadmin");
    QString userpwd = QString("pdmwadmin");
    QString vaultaddr = QString("localhost");
    err = context->vault()->login(username, userpwd, vaultaddr, NULL, NULL);
    QVERIFY2(err==0, qPrintable(QString("Login failed. Error: %1").arg(err)));
    delete context;
}

void TestSldPdmwContext::test_context(){
    SldContext * context = new SldContext();
    QVERIFY2(context->get_swVault() != NULL, "The context has a connection to the vault");
    QVERIFY2(context->vault() != NULL, "The context has a connection to the vault");

    delete context;
}

