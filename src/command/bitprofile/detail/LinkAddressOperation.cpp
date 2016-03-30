#include "LinkAddressOperation.hpp"


namespace Xeth{


LinkAddressOperation::LinkAddressOperation
(
    Ethereum::Connector::Provider &provider, 
    const BitProfile::ProfileDescriptor &descriptor,
    const QString &address,
    const QString &password,
    Notifier &notifier
) : 
    _admin(BitProfile::ProfileAdministrator::FromDescriptor(provider, descriptor)),
    _address(address),
    _password(password),
    _notifier(notifier)
{}


void LinkAddressOperation::operator()()
{
    if(!_admin.setPaymentAddress(_address.toStdString(), _password.toStdString()))
    {
        _notifier.emitError("failed to link stealth address");
    }
}

}
