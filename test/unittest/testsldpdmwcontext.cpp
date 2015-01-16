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

void TestSldPdmwContext::test_open_connection()
{
    SldPdmwContext * vault = new SldPdmwContext();
    IPDMWConnectionPtr swVaultPtr = vault->getVault();
    QVERIFY2(swVaultPtr != NULL, "Failure");

    long err=0;
    BSTR bstr_username = SysAllocString(L"pdmwadmin");
    BSTR bstr_userpwd = SysAllocString(L"pdmwadmin");
    BSTR bstr_vaultserver = SysAllocString(L"172.20.100.13");

    swVaultPtr->Login(bstr_username, bstr_userpwd, bstr_vaultserver, 40000, 30000, &err);
    QVERIFY2(err==0, "Failure to log in");

    delete vault;
}

