#pragma once

#include <QWebFrame>

#include "facade/Notifier.hpp"
#include "facade/WalletFacade.hpp"
#include "facade/AddressBookFacade.hpp"
#include "facade/ConfigFacade.hpp"

#include "synchronizer/Synchronizer.hpp"



namespace Xeth{


class FrameContextBuilder
{
    public:
        FrameContextBuilder(Notifier &, WalletFacade &, AddressBookFacade &, Synchronizer &, ConfigFacade &config);

        void buildContext(QWebFrame *);


    private:
        Notifier &_notifier;
        WalletFacade &_wallet;
        AddressBookFacade &_addressbook;
        Synchronizer &_synchronizer;
        ConfigFacade &_config;
};


}
