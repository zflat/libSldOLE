#include <QString>
#include <QtTest>

#include "Windows.h"
#include <QAxBase>
#include <qaxtypes.h>

#include "comdef.h"
#include "ObjBase.h"

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

