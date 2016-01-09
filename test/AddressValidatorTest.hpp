#pragma once

#include <QObject>
#include <QTest>

#include "wallet/AddressValidator.hpp"


class AddressValidatorTest : public QObject
{
    Q_OBJECT

    private slots:
        void testValidAddress();
        void testAddressTooShort();
        void testInvalidCharacter();

};

