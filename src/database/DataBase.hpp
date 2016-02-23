#pragma once


#include "detail/DataBaseDirectory.hpp"
#include "detail/EthereumKeyStorePath.hpp"

#include "TransactionStore.hpp"
#include "ScanIndexStore.hpp"
#include "AddressBookStore.hpp"
#include "ConfigStore.hpp"
#include "StealthPaymentStore.hpp"
#include "StealthKeyStore.hpp"
#include "EthereumKeyStore.hpp"



namespace Xeth{


class DataBase
{

    public:
        typedef Xeth::TransactionStore TransactionStore;
        typedef Xeth::ScanIndexStore ScanIndexStore;
        typedef Xeth::AddressBookStore AddressBookStore;
        typedef Xeth::ConfigStore ConfigStore;
        typedef Xeth::StealthPaymentStore StealthPaymentStore;
        typedef Xeth::StealthKeyStore StealthKeyStore;
        typedef Xeth::EthereumKeyStore EthereumKeyStore;

    public:
        DataBase(const Settings &);
        DataBase(const DataBaseDirectory &);
        DataBase(const DataBaseDirectory &, const EthereumKeyStorePath &);

        TransactionStore & getTransactions();
        ScanIndexStore & getScanIndex();
        AddressBookStore & getAddressBook();
        ConfigStore & getConfig();
        StealthPaymentStore & getStealthPayments();
        StealthKeyStore & getStealthKeys();
        EthereumKeyStore & getEthereumKeys();

        const TransactionStore & getTransactions() const;
        const ScanIndexStore & getScanIndex() const;
        const AddressBookStore & getAddressBook() const;
        const ConfigStore & getConfig() const;
        const StealthPaymentStore & getStealthPayments() const;
        const StealthKeyStore & getStealthKeys() const;
        const EthereumKeyStore & getEthereumKeys() const;


    private:
        DataBaseDirectory _directory;
        EthereumKeyStorePath _ethereumKeysPath;
        TransactionStore _transactions;
        ScanIndexStore _scanIndex;
        AddressBookStore _addressbook;
        ConfigStore _config;
        StealthPaymentStore _stealthPayments;
        StealthKeyStore _stealthKeys;
        EthereumKeyStore _ethereumKeys;

};



}
