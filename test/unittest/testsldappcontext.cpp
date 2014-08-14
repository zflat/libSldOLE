#include "testsldappcontext.h"
#include "sld_model.h"

TestSldAppContext::TestSldAppContext(QObject *parent) :
    QObject(parent)
{
    if(false){
        SldAppContext * app = new SldAppContext;
        ISldWorksPtr swAppPtr = app->getApp();

        if(swAppPtr){
            IModelDoc2Ptr swModel;

            HRESULT  hres = swAppPtr->get_IActiveDoc2(&swModel);
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
}


void TestSldAppContext::initTestCase()
{
}

void TestSldAppContext::cleanupTestCase()
{
}

void TestSldAppContext::test_open_connection()
{
    SldAppContext * app = new SldAppContext;
    ISldWorksPtr swAppPtr = app->getApp();
    QVERIFY2(swAppPtr != NULL, "Failure");
    delete app;
}

void TestSldAppContext::test_list_open_docs(){

    //////////////////////////////
    /// SETUP
    SldContext * context = new SldContext();
    ISldWorksPtr swAppPtr = context->get_swApp();
    IModelDoc2Ptr* ptrModel;
    QVERIFY2(swAppPtr != NULL, "Failure");


    SldModel* model = new SldModel(context);
    QString part_fname = "SampleA.SLDPRT";
    QString part_path = QDir(DATAROOT).absoluteFilePath("SampleA.SLDPRT");

    bool part_found = QDir(DATAROOT).exists(part_fname);
    QVERIFY2(part_found, "Test data must exist");
    bool path_exists = QDir(part_path).exists(part_path);
    QVERIFY2(path_exists, "Test data must exist");


    bool bres = model->open(part_path, ptrModel);
    QVERIFY2( bres, "SldModel::open failed to open the file");


    /////////////////
    /// TEST VERIFICATIONS
    // qDebug() << part_path.toStdString().c_str();

    QStringList* names = context->app()->open_docs_list();
    QVERIFY2(names->length() > 0, "The list of names must not be empty.");

    for(QStringList::iterator it = names->begin();
        it !=names->end(); ++it){
        QString current = *it;
        // qDebug() << current.toStdString().c_str();
    }
    QVERIFY2(names->contains(part_path.replace("/", "\\")), "The list of names must contain the intenionally opened document.");

    ////////////////////////////////
    /// CLEANUP
    model->close();
    delete model;
    delete context;

}
