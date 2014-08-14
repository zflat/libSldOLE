#ifndef TESTSLDAPPCONTEXT_H
#define TESTSLDAPPCONTEXT_H

#include <QObject>
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
    explicit TestSldAppContext(QObject *parent = 0);

signals:

public slots:

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void test_open_connection();
    void test_list_open_docs();

};

#endif // TESTSLDAPPCONTEXT_H
