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

// const IID IID_SOLIDWORKS="{83A33D31-27C5-11CE-BFD4-00400513BB57}";

TestSldAppContext::TestSldAppContext()
{
    HRESULT Result = NOERROR;

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
                qDebug() << "TEST";
            }
        }
    }
    delete app;

    if(false){
        // skPtr = ISldWorksPtr("SoldWorks.Application");

        // http://adndevblog.typepad.com/manufacturing/2013/08/ccomptr-release.html
        CLSID InvAppClsid;
        Result = CLSIDFromProgID (L"SldWorks.Application", &InvAppClsid);
        if (FAILED(Result)){
            qWarning() << " Could not get CLSID";
            return;
        }

        _com_ptr_t<IUnknownPtr> ptrAppU;
        hres = ptrAppU.CreateInstance(__uuidof(SldWorks), NULL, CLSCTX_LOCAL_SERVER);
        if(FAILED(hres)){
            qWarning() << " Could not ::CreateInstance";
            return;
        }else{

            ptrAppU.GetInterfacePtr();
        }

        IUnknownPtr ptrApp;
        Result = ::GetActiveObject(InvAppClsid, NULL, &ptrApp);


        if (FAILED (Result)){
          qWarning () << "Could not get the active Inventor instance\n";
          return;
        }

        //::CLSIDFromProgID()
    }

    QAxObject* swApp = new QAxObject("SldWorks.Application");

    // http://www.informit.com/articles/article.aspx?p=1405560&seqNum=2
    // qDebug() << swApp->generateDocumentation().toStdString().c_str();

    qDebug() << "COM name: " << swApp->control().toStdString().c_str();

    QAxObject* dObj = swApp->querySubObject("ActiveDoc");
    IModelDoc2 *doc2;
    swApp->queryInterface(IID_IModelDoc2, (void **)&doc2);

    if(!dObj || dObj->isNull()){
        qDebug() << "querySubObject to ActiveDoc failed";
    }else{
        qDebug() << "querySubObject returned " << dObj->className();
        // qDebug() << dObj->generateDocumentation().toStdString().c_str();
        foreach(QString v, dObj->verbs()){
            qDebug() << v.toStdString().c_str();
        }
    }


    QVariant doc = swApp->property("ActiveDoc");

    //http://thrysoee.dk/InsideCOM+/ch05d.htm

    //http://translate.google.com/translate?sl=fr&tl=en&js=y&prev=_t&hl=en&ie=UTF-8&u=http%3A%2F%2Ffr.openclassrooms.com%2Fforum%2Fsujet%2Fqt-ajouter-une-dll-a-son-prog-en-utilisant-idl&edit-text=
    // http://translate.google.com/translate?sl=auto&tl=en&js=y&prev=_t&hl=en&ie=UTF-8&u=http%3A%2F%2Fwww.qtfr.org%2Fviewtopic.php%3Fid%3D9635&edit-text=&act=url

    if(! doc.isNull() ){
        qDebug() << "doc QVariant typeName: " << doc.typeName();
            IDispatch* d= doc.value<IDispatch*>();

            if(d){
                qDebug() << "Cast to IDispatch succeded";
                QAxObject dObj(d);

                if(!dObj.isNull()){
                    //qDebug() << dObj.generateDocumentation().toStdString().c_str();
                    qDebug() << dObj.property("GetPathName").toString().toStdString().c_str();

                }else{
                    qDebug() << "Convert to QAxObject failed";
                }

            }else{
                qDebug() << "Cast to IDispatch failed";
            }
        }else{
            qDebug() << "Call to ActiveDoc failed";
        }
        // doc.canConvert(SldWorks::ModelDoc2);

    delete swApp;
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
