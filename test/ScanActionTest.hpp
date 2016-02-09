#pragma once

#include <QObject>
#include <QTest>


#include "synchronizer/ScanAction.hpp"
#include "synchronizer/ScanCriteria.hpp"
#include "synchronizer/AccountScanCriterion.hpp"

#include "RandomBlockChain.hpp"




class ScanActionTest : public QObject
{
    Q_OBJECT

    private slots:
        void testStart();
        void testStop();
        void testResume();
        void testComplete();
};


