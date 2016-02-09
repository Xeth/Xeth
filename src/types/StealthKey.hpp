#pragma once



#include "ethstealth/Key.hpp"
#include "ethstealth/Address.hpp"
#include "ethstealth/PaymentResolver.hpp"
#include "ethstealth/SharedSecret.hpp"
#include "ethstealth/KeySerializer.hpp"
#include "ethstealth/KeyGenerator.hpp"
#include "ethstealth/Literal.hpp"
#include "ethstealth/PaymentAddressBuilder.hpp"
#include "ethstealth/PaymentAddress.hpp"
#include "ethstealth/RedeemKeyFactory.hpp"

#include "Cipher.hpp"

namespace Xeth{

using Ethereum::Literal;


typedef Ethereum::Stealth::Key<Cipher> StealthKey;
typedef Ethereum::Stealth::KeySerializer<Cipher> StealthKeySerializer;
typedef Ethereum::Stealth::PaymentResolver<StealthKey> StealthResolver;


}
