#include <QString>
#include <QtTest>

#include "Windows.h"
#include <QAxBase>
#include <qaxtypes.h>

#include "comdef.h"
#include "ObjBase.h"

#include "sld_model.h"

class TestModel : public QObject
{
    Q_OBJECT

public:
    TestModel();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void test_open();
    void test_close();
};

