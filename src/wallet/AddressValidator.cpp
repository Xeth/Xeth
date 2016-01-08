
#include "AddressValidator.hpp"

namespace Xeth{


bool AddressValidator::validateAddress(const QString &addr)
{
    std::string address = addr.toStdString();

    if(address.compare(0, 2, "0x"))
    {
        if(address.length() < 22 || address.find_first_not_of("0123456789abcdefABCDEF", 2) != std::string::npos)
        {
            return false;
        }

    }
    else
    {
        if(address.length() < 20 || address.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
        {
            return false;
        }
    }
    return true;
}


bool AddressValidator::validateStealth(const QString &)
{
    return false;
}


}
