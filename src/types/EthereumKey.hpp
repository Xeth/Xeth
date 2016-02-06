#pragma once 

#include "ethkey/cipher/Scrypt.hpp"
#include "ethkey/cipher/AesCipher.hpp"
#include "ethkey/SecuredKey.hpp"
#include "ethkey/serialization/KeySerializer.hpp"
#include "ethkey/Address.hpp"

namespace Xeth{

typedef Ethereum::AesCipher<Ethereum::Scrypt> EthereumKeyCipher;
typedef Ethereum::SecuredKey<EthereumKeyCipher> EthereumKey;
typedef Ethereum::KeySerializer<EthereumKeyCipher> EthereumKeySerializer;
typedef Ethereum::Address EthereumAddress;

}
