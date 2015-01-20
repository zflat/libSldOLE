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

/**
 * @brief The TestSldPdmwContext class
 *
 * NOTE: Unit testing requires a vault
 * to be installed on this computer.
 * http://help.solidworks.com/2013/English/Installation/install_guide/t_installing_workgroup_pdm_server.htm
 *
 */
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
    void test_login();
    void test_context();
    void test_get_first_doc();
};

#endif // TESTSLDPDMWCONTEXT_H
