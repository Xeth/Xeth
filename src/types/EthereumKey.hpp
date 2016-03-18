#pragma once 

#include "ethkey/key/SecuredKey.hpp"
#include "ethkey/key/Address.hpp"
#include "ethkey/key/KeyGenerator.hpp"

#include "ethkey/serialization/KeySerializer.hpp"
#include "ethkey/serialization/Literal.hpp"


#include "Cipher.hpp"

namespace Xeth{

using Ethereum::Literal;

typedef Ethereum::SecuredKey<Cipher> EthereumKey;
typedef Ethereum::KeySerializer<Cipher> EthereumKeySerializer;


}
