#pragma once


#include <QTest>


#include "synchronizer/AccountScanCriterion.hpp"
#include "synchronizer/ScanCriteria.hpp"

#include "BlockChainSimulator.hpp"


class ScanCriteriaTest : public QObject
{
    Q_OBJECT

    private slots:
        void testScan();
        void testEmptyResultScan();
        void testEmptyChainScan();
        void testRandomOffsetScan();
        void testConsecutiveScan();
};
