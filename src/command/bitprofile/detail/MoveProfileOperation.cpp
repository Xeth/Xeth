#include "MoveProfileOperation.hpp"


namespace Xeth{


MoveProfileOperation::MoveProfileOperation
(
    BitProfileStore &store,
    const BitProfile::ProfileAdministrator &admin,
    const BitProfile::Registrar &registrar,
    const QString &name,
    const QString &password,
    Notifier &notifier
) : 
    _admin(admin),
    _store(store),
    _registrar(registrar),
    _name(name),
    _password(password),
    _notifier(notifier)
{}

void MoveProfileOperation::operator()()
{
    BitProfile::Profile::URI uri = _admin.getProfile().getURI();
    if(!_admin.move(_registrar, _name.toStdString(), _password.toStdString()))
    {
        _notifier.emitError("failed to move profile");
    }
    else
    {
        if(!_store.rename(uri, BitProfile::Profile::URI(_registrar.getURI(), _name.toStdString())))
        {
            _notifier.emitError("failed to rename profile file");
        }
    }
}


}
