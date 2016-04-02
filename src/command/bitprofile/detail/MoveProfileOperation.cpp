#include "MoveProfileOperation.hpp"


namespace Xeth{


MoveProfileOperation::MoveProfileOperation
(
    BitProfileStore &store,
    const BitProfile::ProfileAdministrator &admin,
    const BitProfile::Registrar &registrar,
    const QString &name,
    const QString &password,
    const BigInt &gas,
    Notifier &notifier
) : 
    _admin(admin),
    _store(store),
    _registrar(registrar),
    _name(name),
    _password(password),
    _gas(gas),
    _notifier(notifier),
    _uri(_admin.getProfile().getURI())
{}

void MoveProfileOperation::operator()()
{
    try
    {
        if(!_admin.move(_registrar, _name.toStdString(), _password.toStdString(), _gas))
        {
            emitError("failed to move profile");
        }
        else
        {
            if(!_store.rename(_uri, BitProfile::Profile::URI(_registrar.getURI(), _name.toStdString())))
            {
                emitError("failed to rename profile file");
            }
        }
    }
    catch(const std::exception &e)
    {
        emitError(e.what());
    }
    catch(...)
    {
        emitError("failed to rename profile");
    }
}

void MoveProfileOperation::emitError(const char *msg)
{
    _notifier.emitObjectError("bitprofile",  _uri.toString().c_str(), msg);
}

}
