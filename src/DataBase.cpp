#include "DataBase.hpp"


namespace Xeth{

DataBase::DataBase() :
    _directory(true),
    _transactions(_directory.getPath() + "transactions"),
    _scanIndex(_directory.getPath()  + "scanindex"),
    _addressbook(_directory.getPath() + "addressbook")
{}


DataBase::DataBase(const char *path) :
    _directory(path, true),
    _transactions(_directory.getPath().c_str()),
    _scanIndex(_directory.getPath() + "scanindex"),
    _addressbook(_directory.getPath() + "addressbook")
{}

TransactionStore & DataBase::getTransactions()
{
    return _transactions;
}

ScanIndexStore & DataBase::getScanIndex()
{
    return _scanIndex;
}

AddressBookStore & DataBase::getAddressBook()
{
    return _addressbook;
}

const TransactionStore & DataBase::getTransactions() const
{
    return _transactions;
}

const ScanIndexStore & DataBase::getScanIndex() const
{
    return _scanIndex;
}

const AddressBookStore & DataBase::getAddressBook() const
{
    return _addressbook;
}



}
