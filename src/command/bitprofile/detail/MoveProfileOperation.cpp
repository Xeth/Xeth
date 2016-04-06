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
    ProfileOperation(admin, password, notifier),
    _store(store),
    _registrar(registrar),
    _name(name),
    _gas(gas)
{}


void MoveProfileOperation::execute()
{
    if(!_admin.move(_registrar, _name.toStdString(), _password.toStdString(), _gas))
    {
        emitError("failed to move profile");
    }
    else
    {
        if(!_store.rename(_admin.getProfile().getURI(), BitProfile::Profile::URI(_registrar.getURI(), _name.toStdString())))
        {
            emitError("failed to rename profile file");
        }
    }
}


}
