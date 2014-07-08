#include <QString>
#include <QtTest>

#include "Windows.h"
#include <QAxBase>
#include <qaxtypes.h>

#include "comdef.h"
#include "ObjBase.h"

// Q_DECLARE_METATYPE(IDispatch*)

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

    qDebug() << QVariant::nameToType("IDispatch*");
    qDebug() << QVariant::nameToType("IDispatch");
    qDebug() << QVariant::typeToName(QVariant::Bool);
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
