
#include "Window.hpp"

#include <QWebFrame>
#include <QWebElementCollection>
#include <iostream>

namespace Xeth{

Window::Window(const char *uri, WalletFacade &wallet, AddressBookFacade &addressbook, Synchronizer &synchronizer, Notifier &notifier) :
    _wallet(wallet),
    _addressbook(addressbook),
    _synchronizer(synchronizer),
    _notifier(notifier)
{

    QObject::connect(page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(addJSObject()));
    QUrl startURL(uri);

    setUrl(startURL);
}


void Window::javaScriptConsoleMessage ( const QString & message, int lineNumber, const QString & sourceID )
{
    qDebug()<<message<<lineNumber<<sourceID;
}

void Window::addJSObject()
{
    QWebFrame *frame = page()->mainFrame();
    frame->addToJavaScriptWindowObject("wallet", &_wallet);
    frame->addToJavaScriptWindowObject("addressbook", &_addressbook);
    frame->addToJavaScriptWindowObject("synchronizer", &_synchronizer);
    frame->addToJavaScriptWindowObject("events", &_notifier);
}

void Window::moveToScreenCenter()
{
    QRect rect = geometry();
    rect.moveCenter(QApplication::desktop()->availableGeometry().center());
    setGeometry(rect);
}



}
