#pragma once

#include <QObject>
#include <QTest>

#include "simulator/KeyStoreSimulator.hpp"
#include "simulator/BlockChainSimulator.hpp"
#include "simulator/ApplicationContext.hpp"

#include "command/wallet/SendCommand.hpp"



class SendCommandTest : public QObject
{
    Q_OBJECT

    public:
        typedef ::ApplicationContext<KeyStoreSimulator, BlockChainSimulator> ApplicationContext;
        typedef ::GethSimulator<KeyStoreSimulator, BlockChainSimulator> GethSimulator;
#if __GETH_SIMULATOR_ENABLED__
    public:
        SendCommandTest();

    private slots:
        void initTestCase();
        void testSend();
        void testSendStealth();
        void testInvalidRequest();
        void testInvalidDestiantion();
        void testInvalidSource();
        void testInvalidPassword();
        void testNotEnoughFunds();
        void cleanupTestCase();

    private:
        ApplicationContext _context;
        Xeth::SendCommand _command;
#endif
};

