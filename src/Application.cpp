#include "Application.hpp"

namespace Xeth{

Application::Application(const Settings &settings, int argc, char* argv[]):
    _app(argc, argv),
    _settings(settings),
    _database(settings),
    _synchronizer(_provider, _database),
    _wallet(settings, _provider, _database, _notifier),
    _addressbook(_database, _notifier),
    _config(_database, _notifier),
    _contextBuilder(_notifier, _wallet, _addressbook, _synchronizer, _config),
    _window("qrc:/index.html", _contextBuilder)
{
    QObject::connect(&_notifier, SIGNAL(Ready()), this, SLOT(synchronize()));
}

void Application::init()
{
    qDebug()<<"initializing";
    if(!_provider.connect())
    {
        qDebug()<<"failed to connect, forking new process";
        _ethProcess.reset(new Xeth::EthProcessSupervisor(_settings));
        size_t cnt = 0;
        while(!_provider.connect()||cnt>5)
        {
            qDebug()<<"failed to connect, retrying in 1 sec";
            cnt++;
            sleep(1);
        }

        qDebug()<<"connect loop ended";

        if(!_provider.isConnected())
        {
            qDebug()<<"failed to connect";
            _notifier.emitError("RPC failed to connect");
            return ;

        }
    }

    qDebug()<<"provider connected, synchronizing";
    _notifier.emitReady();
}

int Application::exec()
{
    _window.setContextMenuPolicy(Qt::NoContextMenu);
    _window.setMinimumSize(960, 600);
    _window.moveToScreenCenter();
    _window.show();
    _initThread.reset(new boost::thread(boost::bind(&Application::init, this)));
    return _app.exec();
}


void Application::synchronize()
{
    qDebug()<<"synchronization started";
    _synchronizer.loadAddresses();
    _synchronizer.synchronize();
}


}
