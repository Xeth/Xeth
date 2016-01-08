#pragma once

#include <QObject>
#include <QTest>


#include "BigInt.hpp"
#include "TransactionCategory.hpp"
#include "synchronizer/AccountScanCriterion.hpp"




class AccountScanCriterionTest : public QObject
{
    Q_OBJECT

    public:
        AccountScanCriterionTest();

    private slots:
        void testSentTransaction();
        void testReceivedTransaction();
        void testMinedTransaction();
        void testUnknownTransaction();


    private:
        Xeth::AccountScanCriterion _criterion;
};


