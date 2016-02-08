#include "ValidateAddressCommand.hpp"


namespace Xeth{


QVariant ValidateAddressCommand::operator()(const QVariantMap &request)
{
    if(!request.contains("address"))
    {
        return QVariant::fromValue(false);
    }
    AddressValidator validator;
    return QVariant::fromValue(validator.validateAddress(request["address"].toString().toStdString()));
}


}
