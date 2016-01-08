#pragma once

#include <QWebView>
#include <QDebug>
#include <QRect>
#include <QApplication>
#include <QDesktopWidget>

#include "Synchronizer.hpp"
#include "WalletFacade.hpp"
#include "Notifier.hpp"

namespace Xeth{

class Window : public QWebView
{
    Q_OBJECT
    
    public:
        explicit Window(const char *, WalletFacade &, Synchronizer &, Notifier &);

        void moveToScreenCenter();

    protected:
        void javaScriptConsoleMessage ( const QString & message, int lineNumber, const QString & sourceID );


    private slots:
        void addJSObject();

    private:
        WalletFacade &_wallet;
        Synchronizer &_synchronizer;
        Notifier &_notifier;

};

}
