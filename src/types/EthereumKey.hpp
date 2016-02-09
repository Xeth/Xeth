#pragma once 

#include "ethkey/SecuredKey.hpp"
#include "ethkey/serialization/KeySerializer.hpp"
#include "ethkey/Address.hpp"
#include "ethkey/KeyGenerator.hpp"

#include "ethkey/Literal.hpp"

#include "Cipher.hpp"

namespace Xeth{

using Ethereum::Literal;

typedef Ethereum::SecuredKey<Cipher> EthereumKey;
typedef Ethereum::KeySerializer<Cipher> EthereumKeySerializer;


}
