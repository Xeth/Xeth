#include "Facade.hpp"


namespace Xeth{


Facade::Facade(const Settings &settings) :
    _settings(settings),
    _ready(false),
    _provider(settings.get("rpc_retry", 1), settings.get("rpc_retry_interval", 10)),
    _database(settings),
    _synchronizer(_provider, _database, settings),
    _process(settings),
    _wallet(settings, _provider, _database, _notifier, _synchronizer),
    _addressbook(_database, _notifier),
    _config(_database, _notifier),
    _converter(_notifier),
    _progress(_synchronizer, _notifier),
    _clipboard(_notifier),
    _filesystem(_notifier),
    _bitprofile(_provider, _database, _notifier, _settings)
{
    FacadeInitializer *initializer = new FacadeInitializer(QThread::currentThread(), _provider, _process, settings.get("testnet", false)?Ethereum::Connector::Test_Net:Ethereum::Connector::Main_Net);
    QThread *thread = new QThread;
    initializer->moveToThread(thread);
    _process.moveToThread(thread);

    _notifier.watch(_synchronizer);
    _notifier.watch(_database);
    

    connect(thread, &QThread::started, initializer, &FacadeInitializer::initialize);
    connect(initializer, &FacadeInitializer::Error, &_notifier, &Notifier::emitError);
    connect(initializer, &FacadeInitializer::Done, this, &Facade::setReady);

    connect(initializer, &FacadeInitializer::Error, thread, &QThread::quit);
    connect(initializer, &FacadeInitializer::Error, initializer, &FacadeInitializer::deleteLater);
    connect(initializer, &FacadeInitializer::Done, thread, &QThread::quit);
    connect(initializer, &FacadeInitializer::Done, initializer, &FacadeInitializer::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}


bool Facade::isReady() const
{
    return _ready;
}


Facade::AddressBook & Facade::getAddressBook()
{
    return _addressbook;
}

Facade::Config & Facade::getConfig()
{
    return _config;
}

Facade::Wallet & Facade::getWallet()
{
    return _wallet;
}

Facade::Converter & Facade::getConverter()
{
    return _converter;
}


Facade::Progress & Facade::getProgress()
{
    return _progress;
}


Facade::Notifier & Facade::getNotifier()
{
    return _notifier;
}


Facade::Clipboard & Facade::getClipboard()
{
    return _clipboard;
}


Facade::FileSystem & Facade::getFileSystem()
{
    return _filesystem;
}


Facade::BitProfile & Facade::getBitProfile()
{
    return _bitprofile;
}

const Settings & Facade::getSettings() const
{
    return _settings;
}

const Facade::Notifier & Facade::getNotifier() const
{
    return _notifier;
}

const Facade::AddressBook & Facade::getAddressBook() const
{
    return _addressbook;
}

const Facade::Config & Facade::getConfig() const
{
    return _config;
}

const Facade::Wallet & Facade::getWallet() const
{
    return _wallet;
}

const Facade::Converter & Facade::getConverter() const
{
    return _converter;
}


const Facade::Progress & Facade::getProgress() const
{
    return _progress;
}


const Facade::Clipboard & Facade::getClipboard() const
{
    return _clipboard;
}


const Facade::FileSystem & Facade::getFileSystem() const
{
    return _filesystem;
}


const Facade::BitProfile & Facade::getBitProfile() const
{
    return _bitprofile;
}

void Facade::setReady()
{
    _ready = true;
    _synchronizer.loadAddresses();
    _synchronizer.synchronize();
    _notifier.emitReady();
}


}
