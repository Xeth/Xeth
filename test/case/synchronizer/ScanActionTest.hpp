#pragma once

#include <QObject>
#include <QTest>


#include "synchronizer/ScanAction.hpp"
#include "synchronizer/ScanCriteria.hpp"
#include "synchronizer/AccountScanCriterion.hpp"

#include "simulator/RandomBlockChain.hpp"
#include "simulator/KeyStoreSimulator.hpp"
#include "simulator/ApplicationContext.hpp"


class ScanActionTest : public QObject
{
    Q_OBJECT

    public:
        typedef ::ApplicationContext<KeyStoreSimulator, RandomBlockChain> ApplicationContext;
        typedef Ethereum::Connector::BlockChain BlockChain;

    private slots:
        void testStart();
        void testStop();
        void testResume();
        void testComplete();


    private:
        ApplicationContext _context;

};


