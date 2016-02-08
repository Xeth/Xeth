#pragma once

#include <QObject>
#include <QTest>

#include "command/wallet/detail/AddressValidator.hpp"


class AddressValidatorTest : public QObject
{
    Q_OBJECT

    private slots:
        void testValidAddress();
        void testAddressTooShort();
        void testInvalidCharacter();

};

