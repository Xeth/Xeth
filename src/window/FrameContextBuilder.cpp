#include "FrameContextBuilder.hpp"

namespace Xeth{

FrameContextBuilder::FrameContextBuilder(Facade &facade):
    _facade(facade)
{}


void FrameContextBuilder::buildContext(QWebFrame *frame)
{
    Facade::Notifier &notifier = _facade.getNotifier();
    if(_facade.isReady())
    {
        FacadeLinker linker(frame, &_facade);
        linker.linkAll();
        QObject::connect(frame, &QWebFrame::loadFinished, &notifier, &Notifier::emitReady);
    }
    else
    {
        FacadeLinker *linker = new FacadeLinker(frame, &_facade);
        QObject::connect(&notifier, &Notifier::Ready, linker, &FacadeLinker::linkObjects);
        QObject::connect(&notifier, &Notifier::Ready, linker, &FacadeLinker::deleteLater);
        QObject::connect(&notifier, &Notifier::Error, linker, &FacadeLinker::deleteLater);
        linker->linkEvents();
    }

}


}
