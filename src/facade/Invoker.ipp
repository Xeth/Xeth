
namespace Xeth{

inline Invoker::Invoker(Notifier &notifier) :
    _notifier(notifier)
{}

template<class Command, class Request>
QVariant Invoker::invoke(Command &command, const Request &request)
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

template<class Command, class Request>
QVariant Invoker::execute(Command &command, const Request &request)
{
    return command(request);
}

template<class Command>
QVariant Invoker::execute(Command &command, const NullCommandArguments &)
{
    return command();
}


}
