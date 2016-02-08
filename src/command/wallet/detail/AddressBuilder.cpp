#include "AddressBuilder.hpp"

namespace Xeth{

std::string AddressBuilder::build(const EthereumKey &key) const
{
    return key.getAddress().toString();
}

std::string AddressBuilder::build(const StealthKey &key) const
{
    StealthAddress address(key);
    return address.toString();
}

}
