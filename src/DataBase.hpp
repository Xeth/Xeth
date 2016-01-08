#pragma once


#include "database/DataBaseDirectory.hpp"
#include "database/TransactionStore.hpp"
#include "database/ScanIndexStore.hpp"
#include "database/AddressBookStore.hpp"


namespace Xeth{


class DataBase
{
    public:
        DataBase();
        DataBase(const char *path);

        TransactionStore & getTransactions();
        ScanIndexStore & getScanIndex();
        AddressBookStore & getAddressBook();

        const TransactionStore & getTransactions() const;
        const ScanIndexStore & getScanIndex() const;
        const AddressBookStore & getAddressBook() const;

    private:
        DataBaseDirectory _directory;
        TransactionStore _transactions;
        ScanIndexStore _scanIndex;
        AddressBookStore _addressbook;
};



}
