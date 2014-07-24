#include <QString>
#include <QtTest>

#include "sld_model.h"
#include "sldcontext.h"
#include "testsldmodel.h"

#include "smartvars.h"

TestSldModel::TestSldModel(QObject *parent) :
    QObject(parent)
{

    SldAppContext * app = new SldAppContext;
    ISldWorksPtr swAppPtr = app->getApp();

    delete app;
}

void TestSldModel::initTestCase()
{
    context = new SldContext();
}

void TestSldModel::cleanupTestCase()
{
    delete context;
}

void TestSldModel::test_open()
{
    SldModel* model = new SldModel(context);
    QString part_fname = "SampleA.SLDPRT";
    QString part_path = QDir(DATAROOT).absoluteFilePath("SampleA.SLDPRT");

    bool part_found = QDir(DATAROOT).exists(part_fname);
    QVERIFY2(part_found, "Test data must exist");
    bool path_exists = QDir(part_path).exists(part_path);
    QVERIFY2(path_exists, "Test data must exist");

    bool bres = model->open(part_path, ptrModel);
    QVERIFY2( bres, "SldModel::open failed to open the file");
    model->close();
    delete model;
}

void TestSldModel::test_close()
{
    SldModel* model = new SldModel(context);
    QString part_fname = "SampleA.SLDPRT";
    QString part_path = QDir(DATAROOT).absoluteFilePath(part_fname);

    bool bres = model->open(part_path, ptrModel);
    QVERIFY2(model->close(), "Could not close open file");
    delete model;
}


void TestSldModel::test_activedoc_ctor(){

    SldModel* model_setup = new SldModel(context);
    QString part_fname = "SampleA.SLDPRT";
    QString part_path = QDir(DATAROOT).absoluteFilePath(part_fname);
    bool bres = model_setup->open(part_path, ptrModel);
    QVERIFY2(bres, "File opened from data root");

    ISldWorksPtr swAppPtr = context->get_swApp();

    IModelDoc2Ptr swModel;
    HRESULT hres = swAppPtr->get_IActiveDoc2(&swModel);

    IModelDoc2* swModelPtr = static_cast<IModelDoc2*>(swModel);
    SldModel* model = new SldModel(context,static_cast<IModelDoc2**>(&swModelPtr));

    QVERIFY2(model_setup->close(), "Could not close open file");
    delete model;
}

void TestSldModel::test_activedoc(){

    SldModel* model = new SldModel(context);
    QString part_fname("SampleA.SLDPRT");
    QString part_path = QDir(DATAROOT).absoluteFilePath(part_fname);
    bool bres = model->open(part_path, ptrModel);
    QVERIFY2(bres, "Could not open open file");

    ISldWorksPtr swAppPtr = context->get_swApp();
    if(swAppPtr){
        IModelDoc2Ptr swModel;

        HRESULT hres = swAppPtr->get_IActiveDoc2(&swModel);
        if (FAILED(hres)){
            qWarning() << " Could not get the active doc";
        }

        if(swModel){
            BSTR bstr_pathname;
            hres= swModel->GetPathName(&bstr_pathname);
            QString pathName;
            QString pathNameRef;

            pathName = QString((QChar*)bstr_pathname, ::SysStringLen(bstr_pathname));

            IModelDoc2* swModelPtr = static_cast<IModelDoc2*>(swModel);
            IModelDoc2** swModelPtrRef = static_cast<IModelDoc2**>(&swModelPtr);

            QVERIFY2(NULL != swModelPtrRef, "Null value for swModelPtr");

            hres= (*swModelPtrRef)->GetPathName(&bstr_pathname);
            pathNameRef = QString((QChar*)bstr_pathname, ::SysStringLen(bstr_pathname));
            QVERIFY2(pathName == pathNameRef, "Path name from IModelDoc2Ptr matches IModelDoc2**");
        }
    }

    QVERIFY2(model->close(), "Could not close open file");
    delete model;
}

void TestSldModel::test_change_color(){
    SldModel* model = new SldModel(context);
    QString part_fname = "SampleA.SLDPRT";
    QString part_path = QDir(DATAROOT).absoluteFilePath(part_fname);
    bool bres = model->open(part_path, ptrModel);
    QVERIFY2(bres, "Could not open open file");

    VARIANT mat_props0;
    model->iptr()->get_MaterialPropertyValues(static_cast<VARIANT*>(&mat_props0));
    SafeDoubleArray arr_mat_props0(mat_props0);

    model->change_color();

    VARIANT mat_props1;
    model->iptr()->get_MaterialPropertyValues(static_cast<VARIANT*>(&mat_props1));
    SafeDoubleArray arr_mat_props1(mat_props1);

    double clr_val(arr_mat_props1[0]);
    for(uint i=0; i<=2 && i < arr_mat_props1.getSize() ; i++){
        QVERIFY2(arr_mat_props1[i] != arr_mat_props0[i], "Material color is changed");
        if(i>0){
            QVERIFY2(arr_mat_props1[i] != clr_val, "Not all color components are equal");
        }

        qDebug() << i << " " << arr_mat_props1[i];
    }
    QTest::qSleep(1500);

    QVERIFY2(model->close(), "Could not close open file");
    delete model;
}
