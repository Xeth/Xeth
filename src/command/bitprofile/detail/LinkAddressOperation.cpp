#include "LinkAddressOperation.hpp"


namespace Xeth{


LinkAddressOperation::LinkAddressOperation
(
    const BitProfile::ProfileAdministrator &admin,
    const QString &address,
    const QString &password,
    Notifier &notifier
) : 
    _admin(admin),
    _address(address),
    _password(password),
    _notifier(notifier)
{}


void LinkAddressOperation::operator()()
{
    try
    {
        if(!_admin.setPaymentAddress(_address.toStdString(), _password.toStdString()))
        {
            _notifier.emitError("failed to link stealth address");
        }
        else
        {
            _notifier.emitProfilePaymentAddress(_admin.getProfile().getURI().toString().c_str(), _address);
        }
    }
    catch(const std::exception &e)
    {
        _notifier.emitError(e.what());
    }
    catch(...)
    {
        _notifier.emitError("failed to link stealth address");
    }
}

}
