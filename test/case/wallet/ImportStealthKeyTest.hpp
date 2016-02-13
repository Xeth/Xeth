#pragma once

#include <QObject>
#include <QTest>

#include "simulator/KeyStoreSimulator.hpp"
#include "simulator/BlockChainSimulator.hpp"
#include "simulator/ApplicationContext.hpp"

#include "command/wallet/ImportStealthKeyCommand.hpp"



class ImportStealthKeyTest : public QObject
{
    Q_OBJECT

    public:
        typedef ::ApplicationContext<KeyStoreSimulator, BlockChainSimulator> ApplicationContext;
        typedef ::GethSimulator<KeyStoreSimulator, BlockChainSimulator> GethSimulator;

    public:
        ImportStealthKeyTest();

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
};

