#include "Facade.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include "process/ProcessErrorHandler.hpp"
#include "detail/WaitForRpcServer.hpp"


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
    _bitprofile(_provider, _database, _synchronizer, _notifier, _settings, _invoker),
    _network(_provider, _invoker),
    _blockchain(_provider, _notifier, _synchronizer, _invoker),
    _info(_settings, _notifier, _invoker)
{

    Ethereum::Connector::NetworkParams netParams = settings.get("testnet", false)?Ethereum::Connector::Test_Net:Ethereum::Connector::Main_Net;
    _eth.attach(EthProcessFactory::Create(settings));
    _eth.addLoader(WaitForRpcServer(_provider, netParams));

    _provider.onError(ProcessErrorHandler(_eth, settings.get("restart_limit", 10)));

    _ipfs.attach(IpfsProcessFactory::CreateDaemon(settings));

    ChildrenInitializer *initializer = new ChildrenInitializer(QThread::currentThread(), _provider, _eth, _ipfs, netParams, settings);
    QThread *thread = new QThread;
    initializer->moveToThread(thread);
    _eth.moveToThread(thread);
    _ipfs.moveToThread(thread);

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

Facade::Network & Facade::getNetwork()
{
    return _network;
}


Facade::BlockChain & Facade::getBlockChain()
{
    return _blockchain;
}


Facade::Info & Facade::getInfo()
{
    return _info;
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


const Facade::Network & Facade::getNetwork() const
{
    return _network;
}


const Facade::BlockChain & Facade::getBlockChain() const
{
    return _blockchain;
}


const Facade::Info & Facade::getInfo() const
{
    return _info;
}


void Facade::setReady()
{
    if(!_ready)
    {
        _ready = true;
        _synchronizer.loadAddresses();
        _synchronizer.synchronize();
        _notifier.emitReady();
        _info.checkVersionAsync();
    }
}


void Facade::shutdown()
{
    qDebug()<<"shutting down ...";
    _invoker.waitToComplete();
    _synchronizer.stop();
    _ipfs.stop();
    _eth.stop();
}


}
