#ifndef TESTSLDPDMWCONTEXT_H
#define TESTSLDPDMWCONTEXT_H

#include <QObject>
#include <QString>
#include <QtTest>

#include "Windows.h"
#include <QAxBase>
#include <qaxtypes.h>

#include "comdef.h"
#include "ObjBase.h"

#include "sld_pdmw_context.h"

class TestSldPdmwContext : public QObject
{
    Q_OBJECT
public:
    explicit TestSldPdmwContext(QObject *parent = 0);

signals:

public slots:

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void test_open_connection();
};

#endif // TESTSLDPDMWCONTEXT_H
