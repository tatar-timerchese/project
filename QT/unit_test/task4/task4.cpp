#include <QtTest>
#include "./../../../functions.h"

class task4_unit_test : public QObject
{
    Q_OBJECT

public:
    task4_unit_test();
    ~task4_unit_test();

private slots:
    void test_case1();
    void test_case2();

};

task4_unit_test::task4_unit_test()
{

}

task4_unit_test::~task4_unit_test()
{

}

void task4_unit_test::test_case1()
{
    QStringList params;
    params.push_back("8"); 
    params.push_back("2");
    params.push_back("5");
    params.push_back("3");
    params.push_back("1");
    params.push_back("1");
    params.push_back("1");
    params.push_back("5");
    params.push_back("1");
    params.push_back("2");

    QCOMPARE(task4(params, 0), "Correct answer");
}

void task4_unit_test::test_case2()
{
    QStringList params;
    params.push_back("999"); 
    params.push_back("2");
    params.push_back("5");
    params.push_back("3");
    params.push_back("1");
    params.push_back("1");
    params.push_back("1");
    params.push_back("5");
    params.push_back("1");
    params.push_back("2");

    QCOMPARE(task4(params, 0), "Wrong answer, right answer 8");
}

QTEST_APPLESS_MAIN(task4_unit_test)
