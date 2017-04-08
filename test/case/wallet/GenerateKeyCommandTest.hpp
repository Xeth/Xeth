#pragma once

#include <QObject>
#include <QTest>

#include "simulator/KeyStoreSimulator.hpp"
#include "simulator/BlockChainSimulator.hpp"
#include "simulator/ApplicationContext.hpp"

#include "command/wallet/GenerateKeyCommand.hpp"



class GenerateKeyCommandTest : public QObject
{
    Q_OBJECT

    public:
        typedef ::ApplicationContext<KeyStoreSimulator, BlockChainSimulator> ApplicationContext;
        typedef ::GethSimulator<KeyStoreSimulator, BlockChainSimulator> GethSimulator;

#if __GETH_SIMULATOR_ENABLED__
    public:
        GenerateKeyCommandTest();

    private slots:
        void testGenerateEthereumKey();
        void testGenerateStealthKey();
        void testInvalidType();
        void testGenerateFromEntropy();
        void testInvalidEntropy();
        void testInvalidPassword();
        void cleanupTestCase();

    private:
        template<class Iterator>
        size_t getSize(Iterator begin, Iterator end);

    private:
        ApplicationContext _context;
#endif
};

