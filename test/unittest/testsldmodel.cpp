#include <QString>
#include <QtTest>

#include "Windows.h"
#include <QAxBase>
#include <qaxtypes.h>

#include "comdef.h"
#include "ObjBase.h"

#include "sld_model.h"
#include "sld_app_context.h"

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
}

void TestSldModel::cleanupTestCase()
{
}

void TestSldModel::test_open()
{
    QVERIFY2(true, "Failure");
}

void TestSldModel::test_close()
{
    QVERIFY2(true, "Failure");
}
