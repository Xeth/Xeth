#include "DataBase.hpp"


namespace Xeth{



DataBase::DataBase(const Settings &settings) :
    _directory(settings.get("database"), true),
    _ethereumKeysPath(settings),
    _transactions(_directory.getPath().c_str()),
    _scanIndex(_directory.getPath() + "scanindex"),
    _addressbook(_directory.getPath() + "addressbook"),
    _config(_directory.getPath() + "config"),
    _stealthPayments(_directory.getPath() + "stealth"),
    _stealthKeys(_directory.getPath()+"keys"),
    _ethereumKeys(_ethereumKeysPath.toString())
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

StealthPaymentStore & DataBase::getStealthPayments()
{
    return _stealthPayments;
}

StealthKeyStore & DataBase::getStealthKeys()
{
    return _stealthKeys;
}

EthereumKeyStore & DataBase::getEthereumKeys()
{
    return _ethereumKeys;
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


const StealthPaymentStore & DataBase::getStealthPayments() const
{
    return _stealthPayments;
}

const StealthKeyStore & DataBase::getStealthKeys() const
{
    return _stealthKeys;
}

const EthereumKeyStore & DataBase::getEthereumKeys() const
{
    return _ethereumKeys;
}

}
