

#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "include/tst_testsldappcontext.h"

int main(int argc, char *argv[]){

    //Handling CoInitialize (and CoUninitialize!)
    // http://stackoverflow.com/questions/2979113/qcroreapplication-qapplication-with-wmi
    HRESULT hres =  CoInitializeEx(0, COINIT_MULTITHREADED);

    // Construct application before running tests
    // http://stackoverflow.com/a/16711202
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);

    TestSldAppContext test1;
    QTest::qExec(&test1, argc, argv);

    qApp->exit(0);

    CoUninitialize();
    return 0;
}


#include "libSldOLE_unittest_main.moc"