#ifndef TESTM3DHELPER_H
#define TESTM3DHELPER_H

#include <QObject>
#include "libsldole_global.h"
#include "sldcontext.h"

#include "m3d_helper.h"

class TestM3dHelper : public QObject
{
    Q_OBJECT
public:
    explicit TestM3dHelper(QObject *parent = 0);

signals:

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void test_multiply_transform();

private:
    SldContext * context;
    IModelDoc2Ptr *ptrModel;
    M3dHelper * math;

};

#endif // TESTM3DHELPER_H
