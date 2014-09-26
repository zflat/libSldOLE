#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "testsldmodel.h"
#include "testsldappcontext.h"
#include "testm3dhelper.h"

int main(int argc, char *argv[]){

    //Handling CoInitialize (and CoUninitialize!)
    // http://stackoverflow.com/questions/2979113/qcroreapplication-qapplication-with-wmi
    HRESULT hres =  CoInitializeEx(0, COINIT_MULTITHREADED);
    IModelDoc2Ptr ptrModel;

    qDebug() << "DATAROOT: " << DATAROOT;

    // Construct application before running tests
    // http://stackoverflow.com/a/16711202
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    TestSldAppContext test1;
    // QTest::qExec(&test1, argc, argv);

    TestSldModel test2;
    // QTest::qExec(&test2, argc, argv);

    TestM3dHelper test3;
    QTest::qExec(&test3, argc, argv);

    qApp->exit(0);

    CoUninitialize();
    return 0;
}


// #include "libSldOLE_unittest_main.moc"
