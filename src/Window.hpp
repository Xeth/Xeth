#pragma once

#include <QWebView>
#include <QDebug>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>

#include "Synchronizer.hpp"
#include "WalletFacade.hpp"
#include "AddressBookFacade.hpp"
#include "Notifier.hpp"

namespace Xeth{

class Window : public QWebView
{
    Q_OBJECT
    
    public:
        explicit Window(const char *, WalletFacade &, AddressBookFacade &, Synchronizer &, Notifier &);

        void moveToScreenCenter();

    protected:
        void javaScriptConsoleMessage ( const QString & message, int lineNumber, const QString & sourceID );


    private slots:
        void addJSObject();

    private:
        WalletFacade &_wallet;
        AddressBookFacade &_addressbook;
        Synchronizer &_synchronizer;
        Notifier &_notifier;

};

}
