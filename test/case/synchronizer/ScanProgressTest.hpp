#pragma once

#include <QTest>
#include <QSignalSpy>

#include "synchronizer/ScanProgress.hpp"


class ScanProgressTest : public QObject
{
    Q_OBJECT

    private slots:
        void testStep();
        void testComplete();
        void testReuse();
        void testOverflow();
        void testSignal();
        void testCompleteSignal();

};
