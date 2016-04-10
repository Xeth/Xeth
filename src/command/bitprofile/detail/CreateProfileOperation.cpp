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
    try
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
    catch(const std::exception &e)
    {
        emitError(e.what());
    }
    catch(...)
    {
        emitError("create profile operation failed");
    }
}


void CreateProfileOperation::emitError(const char *msg)
{
    QString error = msg;
    error += _name;
    _notifier.emitError("bitprofile", error);
}


}
