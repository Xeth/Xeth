#pragma once 

#include "ethcrypto/key/SecuredKey.hpp"
#include "ethcrypto/key/Address.hpp"
#include "ethcrypto/key/KeyGenerator.hpp"

#include "ethcrypto/serialization/KeySerializer.hpp"
#include "ethcrypto/serialization/Literal.hpp"
#include "ethcrypto/checksum/HexCaseCheckSum.hpp"

#include "Cipher.hpp"

namespace Xeth{

using Ethereum::Literal;

typedef Ethereum::SecuredKey<Cipher> EthereumKey;
typedef Ethereum::KeySerializer<Cipher> EthereumKeySerializer;
typedef Ethereum::HexCaseCheckSum EthereumCheckSum;

}
