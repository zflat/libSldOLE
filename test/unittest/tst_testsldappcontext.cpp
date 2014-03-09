#include <QString>
#include <QtTest>

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
