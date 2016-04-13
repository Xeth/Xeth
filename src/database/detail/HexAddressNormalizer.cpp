#include "HexAddressNormalizer.hpp"


namespace Xeth{

std::string HexAddressNormalizer::operator()(const std::string &address) const
{
    return normalize(address);
}


std::string HexAddressNormalizer::normalize(const std::string &address) const
{
    std::string result = address;
    if(result[1]=='x'||result[1]=='X')
    {
        result.erase(0, 2);
    }

    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

}
