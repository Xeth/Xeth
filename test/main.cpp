
#include <QTest>

#include "AddressBookStoreTest.hpp"
#include "ScanIndexStoreTest.hpp"
#include "TransactionStoreTest.hpp"
#include "AccountScanCriterionTest.hpp"
#include "ScanCriteriaTest.hpp"
#include "ScanProgressTest.hpp"
#include "DataRangeTest.hpp"
#include "AddressValidatorTest.hpp"


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
   return status;
}
