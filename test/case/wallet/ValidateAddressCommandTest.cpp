#include "ValidateAddressCommandTest.hpp"

void ValidateAddressCommandTest::testValidAddress()
{
    Xeth::ValidateAddressCommand validator;

    QVariantMap request;
    request["address"] = "0x2a65aca4d5fc5b5c859090a6c34d164135398226";
    request["checksum"] = false;
    QVERIFY(validator(request).toBool());

    request["address"] = "2a65aca4d5fc5b5c859090a6c34d164135398226";
    QVERIFY(validator(request).toBool());
}


void ValidateAddressCommandTest::testAddressTooShort()
{
    Xeth::ValidateAddressCommand validator;

    QVariantMap request;
    request["address"] = "0x2a65aca4d5fc5b5c859";
    request["checksum"] = false;

    QVERIFY(!validator(request).toBool());

    request["address"] = "2a65aca4d5fc5b5c859";
    QVERIFY(!validator(request).toBool());
}


void ValidateAddressCommandTest::testInvalidCharacter()
{

    Xeth::ValidateAddressCommand validator;
    QVariantMap request;
    request["address"] = "0x2a65aca4d5fc5b5c859090a6c34d164135398226K";
    request["checksum"] = false;

    QVERIFY(!validator(request).toBool());

    request["address"] = "2a65aca4d5fc5b5c859090a6c34d164135398226K";
    QVERIFY(!validator(request).toBool());

}


void ValidateAddressCommandTest::testChecksumAddress()
{
    Xeth::ValidateAddressCommand validator;
    QVERIFY(validator("0xa9e4E3b1DA2462752AeA980698c335E70E9AB26C").toBool());
    QVERIFY(validator("a9e4E3b1DA2462752AeA980698c335E70E9AB26C").toBool());
}

void ValidateAddressCommandTest::testInvalidChecksumAddress()
{
    Xeth::ValidateAddressCommand validator;
    QVERIFY(validator("0xa9E4E3b1DA2462752AeA980698c335E70E9AB26C").toBool() == false);
    QVERIFY(validator("a9E4E3b1DA2462752AeA980698c335E70E9AB26C").toBool() == false);
}

void ValidateAddressCommandTest::testStealthAddress()
{
    Xeth::ValidateAddressCommand validator;
    QVERIFY(validator("3oTYZ99VRU4oAqBarSjVAGZpQ1XfyftWkQYJQZKSRAzWAzCizPFS4sqrfZFXhgpQ473jVUJ5mZ5EYviUp9dfPsnD2kQgLWzFtshbCRf").toBool());
}

void ValidateAddressCommandTest::testInvalidStealthAddress()
{
    Xeth::ValidateAddressCommand validator;
    QVERIFY(validator("3oTYZ99VRU4oAqBarSjVAGZpQ1XfyftWkQYJQZKSRAzWAzCizPFS4sqrfZFXhgpQ473jVUJ5mZ5EYviUp9dfPsnD2kQgLWzFtshbCR1").toBool() == false);
}
