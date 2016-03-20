#include "ValidateAddressCommand.hpp"


namespace Xeth{


QVariant ValidateAddressCommand::operator()(const QString &request)
{
    return validateAddress(request, true);
}


QVariant ValidateAddressCommand::operator()(const QVariantMap &request)
{
    bool checksum = request.contains("checksum") ? request["checksum"].toBool() : true;
    return validateAddress(request["address"].toString(), checksum);
}


bool ValidateAddressCommand::isHexAddress(const QString &request)
{
    size_t length = request.length();
    return (length==40||(length==42&&(request[1]=='x'||request[1]=='X')));
}


QVariant ValidateAddressCommand::validateAddress(const QString &request, bool checksum)
{
    if(isHexAddress(request))
    {
        return validateHexAddress(request, checksum);
    }
    return validateStealthAddress(request, checksum);
}


QVariant ValidateAddressCommand::validateHexAddress(const QString &request, bool checksum)
{
    AddressValidator validator;
    return QVariant::fromValue(validator.validateAddress(request.toStdString(), true));
}


QVariant ValidateAddressCommand::validateStealthAddress(const QString &request, bool checksum)
{
    try
    {
        Ethereum::Stealth::Address address = Literal<Ethereum::Stealth::Address>(request.toStdString());
    }
    catch(...)
    {
        return QVariant::fromValue(false);
    }

    return QVariant::fromValue(true);
}


}
