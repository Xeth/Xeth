#pragma once

#include <QTest>

#include "StoreSimulator.hpp"

#include "database/StoreRange.hpp"


class StoreRangeTest : public QObject
{
    Q_OBJECT

    public:
        typedef StoreSimulator<int> Store;
        typedef Xeth::StoreRange<Store> StoreRange;

    private:
        Store makeStore();

    private slots:
        void testLimit();
        void testOffset();
        void testLimitOverflow();
        void testOffsetOverflow();
};

