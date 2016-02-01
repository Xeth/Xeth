
#include <QApplication>


#include <boost/shared_ptr.hpp>

#include "ethrpc/Provider.hpp"

#include "Settings.hpp"
#include "DataBase.hpp"
#include "Synchronizer.hpp"
#include "WalletFacade.hpp"
#include "AddressBookFacade.hpp"
#include "ConfigFacade.hpp"
#include "Notifier.hpp"

#include "FrameContextBuilder.hpp"
#include "Window.hpp"

#include "EthProcessSupervisor.hpp"


namespace Xeth{

class Application : public QObject
{
    Q_OBJECT
    public:
        Application(const Settings &, int argc, char* argv[]);
        int exec();

    private:
        void init();

    private slots:
        void synchronize();

    private:
        QApplication _app;
        const Settings &_settings;
        Notifier _notifier;
        Ethereum::Connector::Provider _provider;
        DataBase _database;
        Synchronizer _synchronizer;
        boost::shared_ptr<boost::thread> _initThread;
        boost::shared_ptr<EthProcessSupervisor> _ethProcess;
        WalletFacade _wallet;
        AddressBookFacade _addressbook;
        ConfigFacade _config;
        FrameContextBuilder _contextBuilder;
        Window _window;
};

}
