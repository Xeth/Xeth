#include "ValidateStealthAddressCommand.hpp"

namespace Xeth{

QVariant ValidateStealthAddressCommand::operator()(const QString &request) 
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
