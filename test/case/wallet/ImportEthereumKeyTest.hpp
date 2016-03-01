#pragma once

#include <QObject>
#include <QTest>

#include "simulator/KeyStoreSimulator.hpp"
#include "simulator/BlockChainSimulator.hpp"
#include "simulator/ApplicationContext.hpp"

#include "command/wallet/ImportEthereumKeyCommand.hpp"



class ImportEthereumKeyTest : public QObject
{
    Q_OBJECT

    public:
        typedef ::ApplicationContext<KeyStoreSimulator, BlockChainSimulator> ApplicationContext;
        typedef ::GethSimulator<KeyStoreSimulator, BlockChainSimulator> GethSimulator;

#if __GETH_SIMULATOR_ENABLED__

    public:
        ImportEthereumKeyTest();

    private slots:
        void testImport();
        void testInvalidRequest();
        void testMalformedFile();
        void testRenamedFile();
        void testImportNonExistendFile();
        void cleanupTestCase();

    private:
        template<class Iterator>
        size_t getSize(Iterator begin, Iterator end);

    private:
        ApplicationContext _context;
#endif
};

