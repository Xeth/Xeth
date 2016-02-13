#pragma once

#include <QTest>



#include "command/converter/FromFinneyCommand.hpp"
#include "command/converter/ToFinneyCommand.hpp"


class FinneyConversionTest : public QObject
{
    Q_OBJECT
    private slots:
        void testFromFinney();
        void testToFinney();
        void testFromFinneyInvalidParams();
        void testToFinneyInvalidParams();

};

