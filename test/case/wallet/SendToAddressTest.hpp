#pragma once

#include <QObject>
#include <QTest>

#include "simulator/KeyStoreSimulator.hpp"
#include "simulator/BlockChainSimulator.hpp"
#include "simulator/ApplicationContext.hpp"

#include "command/wallet/SendToAddressCommand.hpp"



class SendToAddressTest : public QObject
{
    Q_OBJECT

    public:
        typedef ::ApplicationContext<KeyStoreSimulator, BlockChainSimulator> ApplicationContext;
        typedef ::GethSimulator<KeyStoreSimulator, BlockChainSimulator> GethSimulator;

    public:
        SendToAddressTest();

    private slots:
        void testSend();
        void testInvalidRequest();
        void testInvalidDestiantion();
        void testInvalidSource();
        void testInvalidPassword();
        void testNotEnoughFunds();
        void cleanupTestCase();

    private:
        ApplicationContext _context;
        Xeth::SendToAddressCommand _command;
};

