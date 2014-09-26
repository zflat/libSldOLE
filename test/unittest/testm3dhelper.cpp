#include <QtTest>

#include "testm3dhelper.h"

TestM3dHelper::TestM3dHelper(QObject *parent) :
    QObject(parent)
{
}

void TestM3dHelper::initTestCase()
{
    context = new SldContext();
    math = new M3dHelper(context);
}

void TestM3dHelper::cleanupTestCase()
{
    delete math;
    delete context;
}

void TestM3dHelper::test_multiply_transform(){

    double vals[3] = {1.0, 0.0, 0.0};
    QVERIFY2(sizeof(vals)/sizeof(vals[0]) == 3, "The values must be 3x1");
    std::vector<double> vect_vals = M3dHelper::makeVector(vals, 3);
    QVERIFY2(vect_vals.size() == 3, "The values must be 3x1");

    double vals_negI[12] = {-1.0, 0.0, 0.0,
                            0.0, 1.0, 0.0,
                            0.0, 0.0, 1.0,
                            0.0, 0.0, 0.0};
    IMathTransformPtr neg = math->xformT(M3dHelper::makeVector(vals_negI, 12), 1.0);


    std::vector<double> same = math->trasform(vect_vals, math->xformI());
    QVERIFY2(same.size() == 3, "The result must be a point");
    for(int i=0; i<3; i++){
        qDebug() << same[i] << "<=>" << vals[i];
        QVERIFY2(same[i]==vals[i], "The identity dos not change the point");
    }

    std::vector<double> reflected = math->trasform(vect_vals, neg);

    QVERIFY2(reflected.size() == 3, "The result must be a point");
    qDebug() << reflected[0];
    qDebug() << reflected[1];
    qDebug() << reflected[2];
    QVERIFY2(reflected[0] == -1, "The point must be reflected with respect to x");
}

