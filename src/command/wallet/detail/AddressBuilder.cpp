#include "AddressBuilder.hpp"

namespace Xeth{

std::string AddressBuilder::build(const EthereumKey &key) const
{
    EthereumCheckSum checksum;
    return checksum.compute(key.getAddress().toString());
}

std::string AddressBuilder::build(const StealthKey &key) const
{
    Ethereum::Stealth::Address address(key);
    return address.toString();
}

}
