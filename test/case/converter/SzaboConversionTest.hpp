#pragma once

#include <QTest>



#include "command/converter/FromSzaboCommand.hpp"
#include "command/converter/ToSzaboCommand.hpp"


class SzaboConversionTest : public QObject
{
    Q_OBJECT
    private slots:
        void testFromSzabo();
        void testToSzabo();
        void testFromSzaboInvalidParams();
        void testToSzaboInvalidParams();

};

