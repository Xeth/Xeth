#include "ValidateAddressCommand.hpp"


namespace Xeth{


QVariant ValidateAddressCommand::operator()(const QString &request)
{
    AddressValidator validator;
    return QVariant::fromValue(validator.validateAddress(request.toStdString(), true));
}


}
