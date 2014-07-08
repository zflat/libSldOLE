#include <QString>
#include <QtTest>

#include "Windows.h"
#include <QAxBase>
#include <qaxtypes.h>

#include "comdef.h"
#include "ObjBase.h"

#include "sld_model.h"
#include "sld_app_context.h"
#include "include/tst_testmodel.h"


TestModel::TestModel()
{

    SldAppContext * app = new SldAppContext;
    ISldWorksPtr swAppPtr = app->getApp();

    delete app;
}

void TestModel::initTestCase()
{
}

void TestModel::cleanupTestCase()
{
}

void TestModel::test_open()
{
    QVERIFY2(true, "Failure");
}

void TestModel::test_close()
{
    QVERIFY2(true, "Failure");
}
