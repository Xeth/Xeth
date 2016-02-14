#include "ConverterFacade.hpp"


namespace Xeth{


ConverterFacade::ConverterFacade(Notifier &notifier) :
    _invoker(notifier)
{}

QVariant ConverterFacade::fromWei(const QVariant &request)
{
    FromWeiCommand command;
    return _invoker.invoke(command, request);
}


QVariant ConverterFacade::toWei(const QVariant &request)
{
    ToWeiCommand command;
    return _invoker.invoke(command, request);
}


QVariant ConverterFacade::fromSzabo(const QVariant &request)
{
    FromSzaboCommand command;
    return _invoker.invoke(command, request);
}


QVariant ConverterFacade::toSzabo(const QVariant &request)
{
    ToSzaboCommand command;
    return _invoker.invoke(command, request);
}


QVariant ConverterFacade::fromFinney(const QVariant &request)
{
    FromFinneyCommand command;
    return _invoker.invoke(command, request);
}


QVariant ConverterFacade::toFinney(const QVariant &request)
{
    ToFinneyCommand command;
    return _invoker.invoke(command, request);
}


}
