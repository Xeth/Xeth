#pragma once

#include "ethkey/cipher/Scrypt.hpp"
#include "ethkey/cipher/AesCipher.hpp"
#include "ethkey/cipher/CipherFactory.hpp"

namespace Xeth{

typedef Ethereum::AesCipher<Ethereum::Scrypt> Cipher;
typedef Ethereum::CipherFactory<Cipher, Ethereum::ScryptParamsGenerator> CipherFactory;


}
