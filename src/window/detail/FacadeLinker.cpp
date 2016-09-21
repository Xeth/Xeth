#include "FacadeLinker.hpp"


namespace Xeth{


FacadeLinker::FacadeLinker(QWebFrame *frame, Facade *facade) :
    _frame(frame),
    _facade(facade)
{

}

void FacadeLinker::linkEvents()
{
    _frame->addToJavaScriptWindowObject("XETH_event", &_facade->getNotifier());
}

void FacadeLinker::linkAll()
{
    linkEvents();
    linkObjects();
}

void FacadeLinker::linkObjects()
{
    _frame->addToJavaScriptWindowObject("XETH_wallet", &_facade->getWallet());
    _frame->addToJavaScriptWindowObject("XETH_addressbook", &_facade->getAddressBook());
    _frame->addToJavaScriptWindowObject("XETH_progress", &_facade->getProgress());
    _frame->addToJavaScriptWindowObject("XETH_convert", &_facade->getConverter());
    _frame->addToJavaScriptWindowObject("XETH_config", &_facade->getConfig());
    _frame->addToJavaScriptWindowObject("XETH_clipboard", &_facade->getClipboard());
    _frame->addToJavaScriptWindowObject("XETH_filesystem", &_facade->getFileSystem());
    _frame->addToJavaScriptWindowObject("XETH_bitprofile", &_facade->getBitProfile());
    _frame->addToJavaScriptWindowObject("XETH_network", &_facade->getNetwork());
}


}
