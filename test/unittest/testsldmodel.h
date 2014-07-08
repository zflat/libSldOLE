#ifndef TESTSLDMODEL_H
#define TESTSLDMODEL_H

#include <QObject>
#include <QString>
#include <QtTest>

#include "Windows.h"
#include <QAxBase>
#include <qaxtypes.h>

#include "comdef.h"
#include "ObjBase.h"

#include "sld_model.h"

class TestSldModel : public QObject
{
    Q_OBJECT
public:
    explicit TestSldModel(QObject *parent = 0);

signals:

public slots:

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void test_open();
    void test_close();
};

#endif // TESTSLDMODEL_H
