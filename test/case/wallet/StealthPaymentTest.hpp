#pragma once

#include <QObject>
#include <QTest>

#include "simulator/KeyStoreAdapter.hpp"
#include "simulator/BlockChainSimulator.hpp"
#include "simulator/ApplicationContext.hpp"

#include "command/wallet/SendToStealthCommand.hpp"
#include "command/wallet/SendToAddressCommand.hpp"



class StealthPaymentTest : public QObject
{
    Q_OBJECT

    public:
        typedef ::ApplicationContext<KeyStoreAdapter, BlockChainSimulator> ApplicationContext;
        typedef ::GethSimulator<KeyStoreAdapter, BlockChainSimulator> GethSimulator;
        typedef BlockChainSimulator::TransactionCollection TransactionCollection;
        typedef Ethereum::Connector::Transaction Transaction;

#if __GETH_SIMULATOR_ENABLED__
    public:
        StealthPaymentTest();

    private slots:
        void initTestCase();
        void testSend();
        void testSpend();
        void testInvalidRequest();
        void testInvalidDestiantion();
        void testInvalidSource();
        void testInvalidPassword();
        void testNotEnoughFunds();
        void cleanupTestCase();

    private:
        void generateStealthKey();
        void generateEthereumKey();

        template<class Generator, class Store>
        void generateKey(Store &store);

        template<class Key, class Store>
        void registerKey(const Key &key, Store &store);

    private:
        ApplicationContext _context;
        Xeth::SendToStealthCommand _command;
#endif
};

