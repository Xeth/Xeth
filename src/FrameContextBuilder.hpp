#pragma once

#include <QWebFrame>

#include "Notifier.hpp"
#include "WalletFacade.hpp"
#include "AddressBookFacade.hpp"
#include "Synchronizer.hpp"


namespace Xeth{


class FrameContextBuilder
{
    public:
        FrameContextBuilder(Notifier &, WalletFacade &, AddressBookFacade &, Synchronizer &);

        void buildContext(QWebFrame *);


    private:
        Notifier &_notifier;
        WalletFacade &_wallet;
        AddressBookFacade &_addressbook;
        Synchronizer &_synchronizer;
};


}
