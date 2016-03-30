#include "BitProfileFacade.hpp"


namespace Xeth{


BitProfileFacade::BitProfileFacade(Ethereum::Connector::Provider &provider, DataBase &database, Notifier &notifier, const Settings &settings) :
    _provider(provider),
    _store(database.getBitProfiles()),
    _notifier(notifier),
    _settings(settings),
    _invoker(notifier)
{}


QVariant BitProfileFacade::createProfile(const QVariantMap &request)
{
    CreateProfileCommand command(_provider, _store, _settings, _notifier);
    return _invoker.invoke(command, request);
}

QVariant BitProfileFacade::listProfiles()
{
    ListProfilesCommand command(_store);
    return _invoker.invoke(command, NullCommandArguments());
}

QVariant BitProfileFacade::listRegistrars(const QVariantMap &request)
{
    ListRegistrarsCommand command(_provider, _settings);
    return _invoker.invoke(command, request);
}

QVariant BitProfileFacade::estimate(const QVariantMap &request)
{
    EstimateProfileOperationCommand command(_provider, _store, _settings);
    return _invoker.invoke(command, request);
}

QVariant BitProfileFacade::linkStealthAddress(const QVariantMap &request)
{
    LinkStealthAddressCommand command(_provider, _store, _notifier);
    return _invoker.invoke(command, request);
}

QVariant BitProfileFacade::moveProfile(const QVariantMap &request)
{
    MoveProfileCommand command(_provider, _store, _settings, _notifier);
    return _invoker.invoke(command, request);
}


QVariant BitProfileFacade::resolvePaymentAddress(const QString &request)
{
    ResolvePaymentAddressCommand command(_provider, _settings);
    return _invoker.invoke(command, request);
}


}
