#include "LinkAddressOperation.hpp"


namespace Xeth{


LinkAddressOperation::LinkAddressOperation
(
    const BitProfile::ProfileAdministrator &admin,
    const QString &address,
    const QString &password,
    Notifier &notifier
) :
    ProfileOperation(admin, password, notifier),
    _address(address)
{}



void LinkAddressOperation::execute()
{
    if(!_admin.setPaymentAddress(_address.toStdString(), _password.toStdString()))
    {
        emitError("failed to link stealth address");
    }
    else
    {
        emitData("payments", _address);
    }
}



}
