#include "DataBase.hpp"


namespace Xeth{

DataBase::DataBase() :
    _directory(true),
    _transactions(_directory.getPath() + "transactions"),
    _scanIndex(_directory.getPath()  + "scanindex"),
    _addressbook(_directory.getPath() + "addressbook"),
    _config(_directory.getPath() + "config")
{}


DataBase::DataBase(const char *path) :
    _directory(path, true),
    _transactions(_directory.getPath().c_str()),
    _scanIndex(_directory.getPath() + "scanindex"),
    _addressbook(_directory.getPath() + "addressbook"),
    _config(_directory.getPath() + "config")
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

ConfigStore & DataBase::getConfig()
{
    return _config;
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

const ConfigStore & DataBase::getConfig() const
{
    return _config;
}


}
