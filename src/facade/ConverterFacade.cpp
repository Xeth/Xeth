#include "ConverterFacade.hpp"


namespace Xeth{


ConverterFacade::ConverterFacade(Invoker<Notifier> &invoker) :
    _invoker(invoker)
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
