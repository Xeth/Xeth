#pragma once

#include <QObject>
#include <QTest>

#include "command/wallet/ValidateAddressCommand.hpp"


class ValidateAddressCommandTest : public QObject
{
    Q_OBJECT

    private slots:
        void testValidAddress();
        void testAddressTooShort();
        void testInvalidCharacter();
        void testChecksumAddress();
        void testInvalidChecksumAddress();
        void testStealthAddress();
        void testInvalidStealthAddress();
};

