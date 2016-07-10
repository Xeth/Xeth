#include "BitProfileFacade.hpp"


namespace Xeth{


BitProfileFacade::BitProfileFacade
(
    Ethereum::Connector::Provider &provider,
    DataBase &database,
    Synchronizer &synchronizer,
    Notifier &notifier,
    const Settings &settings,
    Invoker<Notifier> &invoker
) :
    _provider(provider),
    _database(database),
    _synchronizer(synchronizer),
    _store(database.getBitProfiles()),
    _notifier(notifier),
    _settings(settings),
    _invoker(invoker)
{
    QObject::connect(&database.getBitProfiles(), &BitProfileStore::NewItem, this, &BitProfileFacade::emitProfile);
    QObject::connect(&database.getBitProfiles(), &BitProfileStore::Renamed, this, &BitProfileFacade::emitProfileRename);
}


void BitProfileFacade::emitProfileRename(const QString &oldURI, const BitProfile::ProfileDescriptor &descriptor)
{
    QVariantMap event;
    event["oldURI"] = oldURI;
    event["uri"] = descriptor.getURI().c_str();
    event["context"] = descriptor.getContext().c_str();
    event["id"] = descriptor.getName().c_str();
    emit Renamed(event);
}

void BitProfileFacade::emitProfile(const BitProfile::ProfileDescriptor &descriptor)
{
    QVariantMap event;
    event["id"] = descriptor.getName().c_str();
    event["uri"] = descriptor.getURI().c_str();
    event["context"] = descriptor.getContext().c_str();
    event["account"] = descriptor.getAuthAddress().c_str();
    emit Profile(event);
}

QObject * BitProfileFacade::createProfileAsync(const QVariantMap &request)
{
    CreateProfileCommand command(_provider, _database, _synchronizer, _settings);
    return _invoker.invokeAsync(command, request, true);
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

QObject * BitProfileFacade::linkStealthAddressAsync(const QVariantMap &request)
{
    LinkStealthAddressCommand command(_provider, _store);
    return _invoker.invokeAsync(command, request);
}

QObject * BitProfileFacade::moveProfileAsync(const QVariantMap &request)
{
    MoveProfileCommand command(_provider, _store, _settings);
    return _invoker.invokeAsync(command, request, true);
}


QVariant BitProfileFacade::resolvePaymentAddress(const QString &request)
{
    ResolvePaymentAddressCommand command(_provider, _settings);
    return _invoker.invoke(command, request);
}


QVariant BitProfileFacade::exportProfile(const QVariantMap &request)
{
    ExportProfileCommand command(_provider, _database);
    return _invoker.invoke(command, request);
}

QVariant BitProfileFacade::importProfile(const QString &path)
{
    ImportProfileCommand command(_provider, _database);
    return _invoker.invoke(command, path);
}


QVariant BitProfileFacade::getData(const QVariantMap &request)
{
    GetProfileDataCommand command(_provider, _settings);
    return _invoker.invoke(command, request);
}

QObject * BitProfileFacade::updateDetailsAsync(const QVariantMap &request)
{
    UpdateProfileInfoCommand command(_provider, _store, _settings);
    return _invoker.invokeAsync(command, request);
}

QObject * BitProfileFacade::getDetailsAsync(const QString &uri)
{
    ReadProfileInfoCommand command(_provider, _settings);
    return _invoker.invokeAsync(command, uri);
}


QVariant BitProfileFacade::isIdAvailable(const QString &uri)
{
    CheckAvailabilityCommand command(_provider, _settings);
    return _invoker.invoke(command, uri);
}

QVariant BitProfileFacade::isIdAvailable(const QVariantMap &request)
{
    CheckAvailabilityCommand command(_provider, _settings);
    return _invoker.invoke(command, request);
}

QVariant BitProfileFacade::isIdValid(const QString &uri)
{
    ValidateIdCommand command;
    return _invoker.invoke(command, uri);
}



}
