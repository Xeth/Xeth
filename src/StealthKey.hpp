#pragma once

#include "ethkey/cipher/AesCipher.hpp"

#include "ethstealth/Key.hpp"
#include "ethstealth/Address.hpp"
#include "ethstealth/PaymentResolver.hpp"
#include "ethstealth/SharedSecret.hpp"

namespace Xeth{

typedef Ethereum::AesCipher Cipher;
typedef Cipher::Key CipherKey;

typedef Ethereum::Stealth::Key<Cipher> StealthKey;
typedef Ethereum::Stealth::PaymentResolver<StealthKey> StealthPaymentResolver;
typedef Ethereum::Stealth::Address StealthAddress;
typedef Ethereum::Stealth::SharedSecret StealthSharedSecret;
typedef Ethereum::PublicKey PublicKey;

}
