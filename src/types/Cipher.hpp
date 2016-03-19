#pragma once

#include "ethcrypto/cipher/Scrypt.hpp"
#include "ethcrypto/cipher/AesCipher.hpp"
#include "ethcrypto/cipher/CipherFactory.hpp"

namespace Xeth{

typedef Ethereum::AesCipher<Ethereum::Scrypt> Cipher;
typedef Ethereum::CipherFactory<Cipher, Ethereum::ScryptParamsGenerator> CipherFactory;


}
