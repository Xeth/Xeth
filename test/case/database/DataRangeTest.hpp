#pragma once

#include <QTest>

#include "simulator/StoreSimulator.hpp"

#include "database/DataRange.hpp"


class DataRangeTest : public QObject
{
    Q_OBJECT

    public:
        typedef StoreSimulator<int> Store;
        typedef Xeth::DataRange<Store> DataRange;

    private:
        Store makeStore();

    private slots:
        void testLimit();
        void testOffset();
        void testLimitOverflow();
        void testOffsetOverflow();
};

