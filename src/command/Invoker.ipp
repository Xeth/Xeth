
namespace Xeth{


template<class Notifier>
Invoker<Notifier>::Invoker(Notifier &notifier) :
    _notifier(notifier)
{
    qRegisterMetaType<Xeth::Future>("Future");
}


template<class Notifier>
template<class Command, class Request>
QVariant Invoker<Notifier>::invoke(Command &command, const Request &request)
{
    try
    {
        return execute(command, request);
    }
    catch(std::exception &e)
    {
        _notifier.emitError(e.what());
    }
    catch(...)
    {}

    return QVariant::fromValue(false);
}


template<class Notifier>
template<class Command>
QVariant Invoker<Notifier>::invoke(Command &command)
{
    return invoke(command, NullCommandArguments());
}


template<class Notifier>
template<class Command, class Request>
QVariant Invoker<Notifier>::execute(Command &command, const Request &request)
{
    return command(request);
}



template<class Notifier>
template<class Command>
QVariant Invoker<Notifier>::execute(Command &command, const NullCommandArguments &)
{
    return command();
}


template<class Notifier>
template<class Command, class Request>
Future * Invoker<Notifier>::invokeAsync(Command &command, const Request &request)
{
    QFuture<QVariant> future = QtConcurrent::run(this, &Invoker<Notifier>::invoke<Command, Request>, command, request);
    _futures.addFuture(future);
    return new Future(future);
}


template<class Notifier>
template<class Command>
Future * Invoker<Notifier>::invokeAsync(Command &command)
{
    return invokeAsync(command, NullCommandArguments());
}


template<class Notifier>
void Invoker<Notifier>::waitToComplete()
{
    _futures.waitForFinished();
}



template<class Notifier>
Invoker<Notifier>::~Invoker()
{
    waitToComplete();
}


template<class Notifier>
Invoker<Notifier>::Invoker(const Invoker &)
{}



}
