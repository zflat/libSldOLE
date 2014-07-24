#ifndef TESTSLDMODEL_H
#define TESTSLDMODEL_H

#include <QObject>
#include <QString>
#include <QtTest>


#include "libsldole_global.h"
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
    void test_change_color();
    void test_open();
    void test_close();
    void test_activedoc();
    void test_activedoc_ctor();

private:
    SldContext * context;
    IModelDoc2Ptr *ptrModel;
};

#endif // TESTSLDMODEL_H
