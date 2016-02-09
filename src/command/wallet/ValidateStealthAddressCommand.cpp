#include "ValidateStealthAddressCommand.hpp"

namespace Xeth{

QVariant ValidateStealthAddressCommand::operator()(const QVariantMap &request) 
{
    if(!request.contains("address"))
    {
        return QVariant::fromValue(false);
    }

    try
    {
        Ethereum::Stealth::Address address = Literal<Ethereum::Stealth::Address>(request["address"].toString().toStdString());
        qDebug()<<"address "<<address.toString().c_str()<<" is valid";
    }
    catch(...)
    {
        return QVariant::fromValue(false);
    }

    return QVariant::fromValue(true);
}

}
