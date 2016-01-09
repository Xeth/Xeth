#include "FrameContextBuilder.hpp"

namespace Xeth{

FrameContextBuilder::FrameContextBuilder(Notifier &notifier, WalletFacade &wallet, AddressBookFacade &addressbook, Synchronizer &synchronizer, ConfigFacade &config):
    _notifier(notifier),
    _wallet(wallet),
    _addressbook(addressbook),
    _synchronizer(synchronizer),
    _config(config)
{}


void FrameContextBuilder::buildContext(QWebFrame *frame)
{
    frame->addToJavaScriptWindowObject("wallet", &_wallet);
    frame->addToJavaScriptWindowObject("addressbook", &_addressbook);
    frame->addToJavaScriptWindowObject("synchronizer", &_synchronizer);
    frame->addToJavaScriptWindowObject("events", &_notifier);
    frame->addToJavaScriptWindowObject("config", &_config);
}


}
