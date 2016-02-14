#pragma once 

#include <QObject>
#include <QThread>

#include "ethrpc/Provider.hpp"

#include "../Settings.hpp"

#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"

#include "Notifier.hpp"
#include "AddressBookFacade.hpp"
#include "ConfigFacade.hpp"
#include "ConverterFacade.hpp"
#include "WalletFacade.hpp"
#include "ProgressFacade.hpp"

#include "detail/FacadeInitializer.hpp"

namespace Xeth{


class Facade : public QObject
{
    Q_OBJECT
    public:
        typedef AddressBookFacade AddressBook;
        typedef ConfigFacade Config;
        typedef WalletFacade Wallet;
        typedef ConverterFacade Converter;
        typedef Xeth::Synchronizer Synchronizer;
        typedef Xeth::Notifier Notifier;
        typedef Xeth::ProgressFacade Progress;

    public:
        Facade(const Settings &);

        Notifier & getNotifier();
        AddressBook & getAddressBook();
        Config & getConfig();
        Wallet & getWallet();
        Converter & getConverter();
        Progress & getProgress();

        const Notifier & getNotifier() const;
        const AddressBook & getAddressBook() const;
        const Config & getConfig() const;
        const Wallet & getWallet() const;
        const Converter & getConverter() const;
        const Progress & getProgress() const;

        const Settings & getSettings() const;

    private:
        const Settings &_settings;

        Ethereum::Connector::Provider _provider;

        Notifier _notifier;
        DataBase _database;
        Synchronizer _synchronizer;

        EthProcessSupervisor _process;

        Wallet _wallet;
        AddressBook _addressbook;
        Config _config;
        Converter _converter;
        Progress _progress;
};



}
