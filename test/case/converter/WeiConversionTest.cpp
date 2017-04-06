#include "WeiConversionTest.hpp"


void WeiConversionTest::testFromWei()
{
    Xeth::FromWeiCommand command;
    QVariant request = QString("1000000000000000000");
    QVariant result = command(request);

    QCOMPARE(result.toString(), QString("1.00000000000000000000"));

    request = QString("10000000000000000000000000000000000");
    result = command(request);
    QCOMPARE(result.toString(), QString("10000000000000000.00000000000000000000"));

}


void WeiConversionTest::testToWei()
{
    Xeth::ToWeiCommand command;
    QVariant request = QString("1");
    QVariant result = command(request);

    QCOMPARE(result.toString(), QString("1000000000000000000"));

    request = QString("10000000000000000");
    result = command(request);
    QCOMPARE(result.toString(), QString("10000000000000000000000000000000000"));
}


void WeiConversionTest::testFromWeiInvalidParams()
{
    Xeth::FromWeiCommand command;
    QVariant request = QString("mkatepinawna");
    QVariant result = command(request);
    QVERIFY(!result.toBool());
}


void WeiConversionTest::testToWeiInvalidParams()
{
    Xeth::ToWeiCommand command;
    QVariant request = QString("mkatepinawna");
    QVariant result = command(request);
    QVERIFY(!result.toBool());
}
