#include <QString>
#include <QtTest>

#include "sld_app_context.h"

class TestSldAppContext : public QObject
{
    Q_OBJECT

public:
    TestSldAppContext();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void test_open_connection();
};


TestSldAppContext::TestSldAppContext()
{
    //Handling CoInitialize (and CoUninitialize!)
    // http://stackoverflow.com/questions/2979113/qcroreapplication-qapplication-with-wmi
    HRESULT hres =  CoInitializeEx(0, COINIT_MULTITHREADED);

    SldAppContext * app = new SldAppContext;
    ISldWorksPtr swAppPtr = app->getApp();

    if(swAppPtr){
        IModelDoc2Ptr swModel;
        hres = swAppPtr->get_IActiveDoc2(&swModel);
        if (FAILED(hres)){
            qWarning() << " Could not get the active doc";
        }else if(swModel){
            BSTR pathName;
            (hres) = swModel->GetPathName(&pathName);
            if (FAILED(hres)){
                qWarning() << " Could not get the document path name";
            }else{
                QString qstr((QChar*)pathName, ::SysStringLen(pathName));
                qDebug() << qstr.toStdString().c_str();
            }
        }
    }
    delete app;

    CoUninitialize();
}

void TestSldAppContext::initTestCase()
{
}

void TestSldAppContext::cleanupTestCase()
{
}

void TestSldAppContext::test_open_connection()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestSldAppContext)

#include "tst_testsldappcontext.moc"
