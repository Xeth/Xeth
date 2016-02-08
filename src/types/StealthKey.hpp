#pragma once

#include "ethkey/cipher/Scrypt.hpp"
#include "ethkey/cipher/AesCipher.hpp"
#include "ethkey/cipher/CipherFactory.hpp"

#include "ethstealth/Key.hpp"
#include "ethstealth/Address.hpp"
#include "ethstealth/PaymentResolver.hpp"
#include "ethstealth/SharedSecret.hpp"
#include "ethstealth/KeySerializer.hpp"
#include "ethstealth/KeyGenerator.hpp"
#include "ethstealth/Literal.hpp"
#include "ethstealth/PaymentAddressBuilder.hpp"
#include "ethstealth/PaymentAddress.hpp"


namespace Xeth{

using Ethereum::Literal;


typedef Ethereum::AesCipher<Ethereum::Scrypt> StealthCipher;
typedef Ethereum::ScryptParams StealthCipherParams;
typedef Ethereum::ScryptParamsGenerator StealthCipherParamsGenerator;
typedef Ethereum::Stealth::Key<StealthCipher> StealthKey;
typedef Ethereum::Stealth::KeySerializer<StealthCipher> StealthKeySerializer;
typedef Ethereum::Stealth::PaymentResolver<StealthKey> StealthPaymentResolver;
typedef Ethereum::Stealth::Address StealthAddress;
typedef Ethereum::Stealth::SharedSecret StealthSharedSecret;
typedef Ethereum::Stealth::KeyGenerator StealthKeyGenerator;
typedef Ethereum::CipherFactory<StealthCipher, StealthCipherParamsGenerator> StealthKeyCipherFactory;
typedef Ethereum::PublicKey PublicKey;

typedef Ethereum::Stealth::PaymentAddressBuilder StealthPaymentAddressBuilder;
typedef Ethereum::Stealth::PaymentAddress StealthPaymentAddress;

}
