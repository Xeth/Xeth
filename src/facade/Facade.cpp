#include "Facade.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

namespace Xeth{


Facade::Facade(const Settings &settings) :
    _settings(settings),
    _ready(false),
    _database(settings),
    _synchronizer(_provider, _database, settings),
    _eth(settings),
    _ipfs(settings),
    _invoker(_notifier),
    _wallet(settings, _provider, _database, _notifier, _synchronizer, _invoker),
    _addressbook(_database, _invoker),
    _config(_database, _invoker),
    _converter(_invoker),
    _progress(_synchronizer, _invoker),
    _clipboard(_invoker),
    _filesystem(_invoker),
    _bitprofile(_provider, _database, _synchronizer, _notifier, _settings, _invoker)
{
    _eth.attach(EthProcessFactory::Create(settings));
    _ipfs.attach(IpfsProcessFactory::CreateDaemon(settings));
    ChildrenInitializer *initializer = new ChildrenInitializer(QThread::currentThread(), _provider, _eth, _ipfs, settings.get("testnet", false)?Ethereum::Connector::Test_Net:Ethereum::Connector::Main_Net, settings);
    QThread *thread = new QThread;
    initializer->moveToThread(thread);
    _eth.moveToThread(thread);
    _ipfs.moveToThread(thread);

    _notifier.watch(_synchronizer);
    _notifier.watch(_database);
    

    connect(thread, &QThread::started, initializer, &ChildrenInitializer::initialize);
    connect(initializer, SIGNAL(Error(const QString &)), &_notifier, SLOT(emitError(const QString &)));
    connect(initializer, &ChildrenInitializer::Done, this, &Facade::setReady);

    connect(initializer, &ChildrenInitializer::Error, thread, &QThread::quit);
    connect(initializer, &ChildrenInitializer::Error, initializer, &ChildrenInitializer::deleteLater);
    connect(initializer, &ChildrenInitializer::Done, thread, &QThread::quit);
    connect(initializer, &ChildrenInitializer::Done, initializer, &ChildrenInitializer::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

Facade::~Facade()
{
    _synchronizer.stop();
    _eth.stop();
    _ipfs.stop();
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
    if(!_ready)
    {
        _ready = true;
        _synchronizer.loadAddresses();
        _synchronizer.synchronize();
        _notifier.emitReady();
    }
}


void Facade::shutdown()
{
    qDebug()<<"waiting to complete...";
    _synchronizer.stop();
    _invoker.waitToComplete();
    qDebug()<<"sleeping ...";
    boost::this_thread::sleep(boost::posix_time::milliseconds(10000));
}


}
