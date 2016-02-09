#pragma once

#include <QObject>
#include <QTest>


#include "database/KeyAttributesReader.hpp"



class KeyAttributesReaderTest : public QObject
{
    Q_OBJECT

    private slots:
        void checkStealthKeyCreationTime();
        void checkStealthKeyAddress();
        void checkEthereumKeyCreationTime();
        void checkEthereumKeyAddress();
        void checkNonExistentStealthKey();
        void checkNonExistentEthereumKey();

};


