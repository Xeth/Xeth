#include "FrameContextBuilder.hpp"

namespace Xeth{

FrameContextBuilder::FrameContextBuilder(Facade &facade):
    _facade(facade)
{}


void FrameContextBuilder::buildContext(QWebFrame *frame)
{
    frame->addToJavaScriptWindowObject("xeth.wallet", &_facade.getWallet());
    frame->addToJavaScriptWindowObject("xeth.addressbook", &_facade.getAddressBook());
    frame->addToJavaScriptWindowObject("xeth.progress", &_facade.getProgress());
    frame->addToJavaScriptWindowObject("xeth.events", &_facade.getNotifier());
    frame->addToJavaScriptWindowObject("xeth.convert", &_facade.getConverter());
    frame->addToJavaScriptWindowObject("xeth.config", &_facade.getConfig());
}


}
