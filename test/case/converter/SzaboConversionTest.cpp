#include "SzaboConversionTest.hpp"


void SzaboConversionTest::testFromSzabo()
{
    Xeth::FromSzaboCommand command;
    QVariant request = QString("1000000");
    QVariant result = command(request);

    QCOMPARE(result.toString(), QString("1.00000000000000000000"));

    request = QString("10000000000000000000000");
    result = command(request);
    QCOMPARE(result.toString(), QString("10000000000000000.00000000000000000000"));

}


void SzaboConversionTest::testToSzabo()
{
    Xeth::ToSzaboCommand command;
    QVariant request = QString("1");
    QVariant result = command(request);

    QCOMPARE(result.toString(), QString("1000000"));

    request = QString("10000000000000000");
    result = command(request);
    QCOMPARE(result.toString(), QString("10000000000000000000000"));
}


void SzaboConversionTest::testFromSzaboInvalidParams()
{
    Xeth::FromSzaboCommand command;
    QVariant request = QString("mkatepinawna");
    QVariant result = command(request);
    QVERIFY(!result.toBool());
}


void SzaboConversionTest::testToSzaboInvalidParams()
{
    Xeth::ToSzaboCommand command;
    QVariant request = QString("mkatepinawna");
    QVariant result = command(request);
    QVERIFY(!result.toBool());
}
