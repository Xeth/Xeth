
#include <QTest>
#include <iostream>

#include "AddressBookStoreTest.hpp"
#include "ScanIndexStoreTest.hpp"
#include "TransactionStoreTest.hpp"
#include "AccountScanCriterionTest.hpp"
#include "ScanCriteriaTest.hpp"
#include "ScanProgressTest.hpp"
#include "DataRangeTest.hpp"
#include "AddressValidatorTest.hpp"
#include "BlockChainProgressTest.hpp"
#include "StealthScanCriterionTest.hpp"

int main(int argc, char** argv)
{
    int status = 0;
    {
        AddressBookStoreTest test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        ScanIndexStoreTest test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        TransactionStoreTest test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        AccountScanCriterionTest test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        ScanCriteriaTest test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        ScanProgressTest test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        DataRangeTest test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        AddressValidatorTest test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        BlockChainProgressTest test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        StealthScanCriterionTest test;
        status |= QTest::qExec(&test, argc, argv);
    }
    if(status)
    {
        std::cout<<"\nUnit-Test failed\n";
    }
   return status;
}
