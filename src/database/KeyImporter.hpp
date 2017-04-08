#pragma once 

#include "EthereumKeyStore.hpp"
#include "StealthKeyStore.hpp"
#include "detail/FileImporter.hpp"
#include "detail/EthereumKeyValidator.hpp"
#include "detail/StealthKeyValidator.hpp"


namespace Xeth{


typedef FileImporter<EthereumKeyStore, EthereumKeyValidator> EthereumKeyImporter;
typedef FileImporter<StealthKeyStore, StealthKeyValidator> StealthKeyImporter;


}
