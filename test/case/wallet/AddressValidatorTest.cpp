#include "AddressValidatorTest.hpp"

void AddressValidatorTest::testValidAddress()
{
    Xeth::AddressValidator validator;

    QVERIFY(validator.validateAddress("0x2a65aca4d5fc5b5c859090a6c34d164135398226"));
    QVERIFY(validator.validateAddress("2a65aca4d5fc5b5c859090a6c34d164135398226"));
}


void AddressValidatorTest::testAddressTooShort()
{
    Xeth::AddressValidator validator;

    QVERIFY(!validator.validateAddress("0x2a65aca4d5fc5b5c859"));
    QVERIFY(!validator.validateAddress("2a65aca4d5fc5b5c859"));
}


void AddressValidatorTest::testInvalidCharacter()
{

    Xeth::AddressValidator validator;

    QVERIFY(!validator.validateAddress("0x2a65aca4d5fc5b5c859090a6c34d164135398226K"));
    QVERIFY(!validator.validateAddress("2a65aca4d5fc5b5c859090a6c34d164135398226K"));

}
