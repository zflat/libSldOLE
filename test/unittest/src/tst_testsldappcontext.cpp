#include <QString>
#include <QtTest>

#include "Windows.h"
#include <QAxBase>
#include <qaxtypes.h>

#include "comdef.h"
#include "ObjBase.h"

#include "sld_app_context.h"
#include "include/tst_testsldappcontext.h"


TestSldAppContext::TestSldAppContext()
{

    SldAppContext * app = new SldAppContext;
    ISldWorksPtr swAppPtr = app->getApp();

    if(swAppPtr){
        IModelDoc2Ptr swModel;

        hres = swAppPtr->get_IActiveDoc2(&swModel);
        if (FAILED(hres)){
            qWarning() << " Could not get the active doc";
        }else if(swModel){            
            IModelViewPtr swView;
            hres = swModel->get_IActiveView(&swView);

            BSTR viewName = SysAllocString(L"*Isometric");
            hres = swModel->ShowNamedView2(viewName, -1);
            hres = swModel->ViewZoomtofit2();

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


// #include "tst_testsldappcontext.moc"
