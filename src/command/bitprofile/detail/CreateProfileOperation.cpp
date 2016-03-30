#include "CreateProfileOperation.hpp"


namespace Xeth{


CreateProfileOperation::CreateProfileOperation
(
    const BitProfile::Registrar &registrar,
    const QString &name,
    const QString &account,
    const QString &password,
    BitProfileStore &store,
    Notifier &notifier
) :
    _registrar(registrar),
    _name(name),
    _account(account),
    _password(password),
    _store(store),
    _notifier(notifier)
{}


void CreateProfileOperation::operator()()
{
    BitProfile::ProfileAdministrator profile = BitProfile::ProfileAdministrator::CreateProfile(_registrar, _name.toStdString(), _account.toStdString(), _password.toStdString());
    if(profile.isNull())
    {
        emitError("failed to create account ");
    }
    else
    {
        if(!_store.insert(BitProfile::ProfileDescriptor(profile)))
        {
            emitError("failed to save account ");
        }
    }
}


void CreateProfileOperation::emitError(const char *msg)
{
    QString error = msg;
    error += _name;
    _notifier.emitError(error);
}


}
