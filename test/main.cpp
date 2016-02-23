
#include <QTest>
#include <iostream>

#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#include "case/database/AddressBookStoreTest.hpp"
#include "case/database/ScanIndexStoreTest.hpp"
#include "case/database/TransactionStoreTest.hpp"
#include "case/database/DataRangeTest.hpp"
#include "case/database/StealthKeyStoreTest.hpp"
#include "case/database/EthereumKeyStoreTest.hpp"
#include "case/database/KeyAttributesReaderTest.hpp"
#include "case/database/StealthKeyImporterTest.hpp"
#include "case/database/EthereumKeyImporterTest.hpp"
#include "case/database/StealthPaymentStoreTest.hpp"

#include "case/synchronizer/AccountScanCriterionTest.hpp"
#include "case/synchronizer/ScanCriteriaTest.hpp"
#include "case/synchronizer/ScanProgressTest.hpp"
#include "case/synchronizer/BlockChainProgressTest.hpp"
#include "case/synchronizer/StealthScanCriterionTest.hpp"
#include "case/synchronizer/ScanActionTest.hpp"

#include "case/wallet/AddressValidatorTest.hpp"
#include "case/wallet/SendToAddressTest.hpp"
#include "case/wallet/StealthPaymentTest.hpp"
#include "case/wallet/GenerateEthereumKeyTest.hpp"
#include "case/wallet/GenerateStealthKeyTest.hpp"
#include "case/wallet/ImportKeyTest.hpp"
#include "case/wallet/ImportStealthKeyTest.hpp"
#include "case/converter/WeiConversionTest.hpp"
#include "case/converter/SzaboConversionTest.hpp"
#include "case/converter/FinneyConversionTest.hpp"


template<class Test>
int ExecuteTest(int argc, char **argv)
{
    Test test;
    return QTest::qExec(&test, argc, argv);
}

#define EXECUTE_TEST(r, data, Test) ||ExecuteTest<Test>(argc, argv)
#define RUN_TEST_SEQ(seq) 0 BOOST_PP_SEQ_FOR_EACH(EXECUTE_TEST,, seq )
#define RUN_TESTS(...) RUN_TEST_SEQ(BOOST_PP_VARIADIC_TO_SEQ (__VA_ARGS__))

int main(int argc, char** argv)
{
    int status = RUN_TESTS
    (
        AddressBookStoreTest,
        ScanIndexStoreTest,
        TransactionStoreTest,
        AccountScanCriterionTest,
        ScanCriteriaTest,
        ScanProgressTest,
        DataRangeTest,
        AddressValidatorTest,
        BlockChainProgressTest,
        StealthScanCriterionTest,
        ScanActionTest,
        StealthKeyStoreTest,
        EthereumKeyStoreTest,
        KeyAttributesReaderTest,
        StealthKeyImporterTest,
        EthereumKeyImporterTest,
        StealthPaymentStoreTest,
        SendToAddressTest,
        StealthPaymentTest,
        GenerateEthereumKeyTest,
        GenerateStealthKeyTest,
        ImportKeyTest,
        ImportStealthKeyTest,
        WeiConversionTest,
        SzaboConversionTest,
        FinneyConversionTest
    );

    if(status)
    {
        std::cout<<"\nUnit-Test failed\n";
    }
    return status;
}
