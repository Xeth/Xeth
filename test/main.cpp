
#include <QTest>

#include "AddressBookStoreTest.hpp"
#include "ScanIndexStoreTest.hpp"


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

   return status;
}
