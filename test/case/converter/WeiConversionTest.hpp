#pragma once

#include <QTest>



#include "command/converter/FromWeiCommand.hpp"
#include "command/converter/ToWeiCommand.hpp"


class WeiConversionTest : public QObject
{
    Q_OBJECT
    private slots:
        void testFromWei();
        void testToWei();
        void testFromWeiInvalidParams();
        void testToWeiInvalidParams();

};

