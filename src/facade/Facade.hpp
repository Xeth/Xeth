#pragma once 

#include <QObject>
#include <QThread>

#include "ethrpc/Provider.hpp"
#include "ethrpc/Network.hpp"

#include "conf/Settings.hpp"
#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"
#include "process/ProcessSupervisor.hpp"
#include "process/EthProcessFactory.hpp"
#include "process/IpfsProcessFactory.hpp"

#include "Notifier.hpp"
#include "AddressBookFacade.hpp"
#include "ConfigFacade.hpp"
#include "ConverterFacade.hpp"
#include "WalletFacade.hpp"
#include "ProgressFacade.hpp"
#include "ClipboardFacade.hpp"
#include "FileSystemFacade.hpp"
#include "BitProfileFacade.hpp"
#include "NetworkFacade.hpp"
#include "BlockChainFacade.hpp"
#include "InfoFacade.hpp"

#include "detail/ChildrenInitializer.hpp"

#include "command/Invoker.hpp"


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
        typedef Xeth::ClipboardFacade Clipboard;
        typedef Xeth::FileSystemFacade FileSystem;
        typedef Xeth::BitProfileFacade BitProfile;
        typedef Xeth::NetworkFacade Network;
        typedef Xeth::BlockChainFacade BlockChain;
        typedef Xeth::InfoFacade Info;

    public:
        Facade(Settings &);
        ~Facade();

        DataBase & getDataBase();

        Notifier & getNotifier();
        AddressBook & getAddressBook();
        Config & getConfig();
        Wallet & getWallet();
        Converter & getConverter();
        Progress & getProgress();
        Clipboard & getClipboard();
        FileSystem & getFileSystem();
        BitProfile & getBitProfile();
        Network & getNetwork();
        BlockChain & getBlockChain();
        Info & getInfo();

        const Notifier & getNotifier() const;
        const AddressBook & getAddressBook() const;
        const Config & getConfig() const;
        const Wallet & getWallet() const;
        const Converter & getConverter() const;
        const Progress & getProgress() const;
        const Clipboard & getClipboard() const;
        const FileSystem & getFileSystem() const;
        const BitProfile & getBitProfile() const;
        const Network & getNetwork() const;
        const BlockChain & getBlockChain() const;
        const Info & getInfo() const;

        const Settings & getSettings() const;
        bool isReady() const;

    public slots:
        void shutdown();

    private slots:
        void setReady();

    private:
        Settings &_settings;
        bool _ready;

        Ethereum::Connector::Provider _provider;

        Notifier _notifier;
        DataBase _database;
        Synchronizer _synchronizer;

        ProcessSupervisor _eth;
        ProcessSupervisor _ipfs;

        Invoker<Notifier> _invoker;

        Wallet _wallet;
        AddressBook _addressbook;
        Config _config;
        Converter _converter;
        Progress _progress;
        Clipboard _clipboard;
        FileSystem _filesystem;
        BitProfile _bitprofile;
        Network _network;
        BlockChain _blockchain;
        Info _info;
};



}
