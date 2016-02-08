#pragma once 

#include "ethkey/cipher/Scrypt.hpp"
#include "ethkey/cipher/AesCipher.hpp"
#include "ethkey/SecuredKey.hpp"
#include "ethkey/serialization/KeySerializer.hpp"
#include "ethkey/Address.hpp"
#include "ethkey/KeyGenerator.hpp"
#include "ethkey/cipher/CipherFactory.hpp"

namespace Xeth{

typedef Ethereum::ScryptParamsGenerator EthereumKeyCipherParamsGenerator;
typedef Ethereum::AesCipher<Ethereum::Scrypt> EthereumKeyCipher;
typedef Ethereum::SecuredKey<EthereumKeyCipher> EthereumKey;
typedef Ethereum::KeySerializer<EthereumKeyCipher> EthereumKeySerializer;
typedef Ethereum::KeyGenerator EthereumKeyGenerator;
typedef Ethereum::Address EthereumAddress;
typedef Ethereum::CipherFactory<EthereumKeyCipher, EthereumKeyCipherParamsGenerator> EthereumKeyCipherFactory;

}
