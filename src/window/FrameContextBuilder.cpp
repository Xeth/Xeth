#include "FrameContextBuilder.hpp"

namespace Xeth{

FrameContextBuilder::FrameContextBuilder(Facade &facade):
    _facade(facade)
{}


void FrameContextBuilder::buildContext(QWebFrame *frame)
{
    if(_facade.isReady())
    {
        FacadeLinker linker(frame, &_facade);
        linker.linkAll();
    }
    else
    {
        Facade::Notifier &notifier = _facade.getNotifier();
        FacadeLinker *linker = new FacadeLinker(frame, &_facade);
        QObject::connect(&notifier, &Notifier::Ready, linker, &FacadeLinker::linkObjects);
        QObject::connect(&notifier, &Notifier::Ready, linker, &FacadeLinker::deleteLater);
        QObject::connect(&notifier, &Notifier::Error, linker, &FacadeLinker::deleteLater);
        linker->linkEvents();
    }

}


}
