#pragma once

#include <QObject>
#include <QTest>

#include <boost/shared_ptr.hpp>

#include "synchronizer/StealthScanCriterion.hpp"

#include "types/BigInt.hpp"
#include "types/TransactionCategory.hpp"
#include "types/StealthKey.hpp"





class StealthScanCriterionTest : public QObject
{
    Q_OBJECT

    private slots:
        void testReceivedTransaction();
        void testUnknownTransaction();


    private:
        Xeth::StealthKey makeKey();

};


