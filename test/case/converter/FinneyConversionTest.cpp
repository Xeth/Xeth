#include "FinneyConversionTest.hpp"


void FinneyConversionTest::testFromFinney()
{
    Xeth::FromFinneyCommand command;
    QVariant request = QString("1000");
    QVariant result = command(request);

    QCOMPARE(result.toString(), QString("1"));

    request = QString("10000000000000000000");
    result = command(request);
    QCOMPARE(result.toString(), QString("10000000000000000"));

}


void FinneyConversionTest::testToFinney()
{
    Xeth::ToFinneyCommand command;
    QVariant request = QString("1");
    QVariant result = command(request);

    QCOMPARE(result.toString(), QString("1000"));

    request = QString("10000000000000000");
    result = command(request);
    QCOMPARE(result.toString(), QString("10000000000000000000"));
}


void FinneyConversionTest::testFromFinneyInvalidParams()
{
    Xeth::FromFinneyCommand command;
    QVariant request = QString("mkatepinawna");
    QVariant result = command(request);
    QVERIFY(!result.toBool());
}


void FinneyConversionTest::testToFinneyInvalidParams()
{
    Xeth::ToFinneyCommand command;
    QVariant request = QString("mkatepinawna");
    QVariant result = command(request);
    QVERIFY(!result.toBool());
}
