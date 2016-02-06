#pragma once

#include "ethkey/cipher/Scrypt.hpp"
#include "ethkey/cipher/AesCipher.hpp"

#include "ethstealth/Key.hpp"
#include "ethstealth/Address.hpp"
#include "ethstealth/PaymentResolver.hpp"
#include "ethstealth/SharedSecret.hpp"
#include "ethstealth/KeySerializer.hpp"


namespace Xeth{

typedef Ethereum::AesCipher<Ethereum::Scrypt> Cipher;
typedef Ethereum::ScryptParams CipherParams;
typedef Ethereum::Stealth::Key<Cipher> StealthKey;
typedef Ethereum::Stealth::KeySerializer<Cipher> StealthKeySerializer;
typedef Ethereum::Stealth::PaymentResolver<StealthKey> StealthPaymentResolver;
typedef Ethereum::Stealth::Address StealthAddress;
typedef Ethereum::Stealth::SharedSecret StealthSharedSecret;
typedef Ethereum::PublicKey PublicKey;
}
