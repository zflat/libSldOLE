#include <QString>
#include <QtTest>

#include "sld_model.h"
#include "sldcontext.h"
#include "testsldmodel.h"

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
    QString part_path = QDir(DATAROOT).absoluteFilePath("SampleA.SLDPRT");

    bool bres = model->open(part_path, ptrModel);
    QVERIFY2(model->close(), "Could not close open file");
    delete model;
}
