#pragma once 

#include "EthereumKeyStore.hpp"
#include "StealthKeyStore.hpp"
#include "detail/FileImporter.hpp"


namespace Xeth{


typedef FileImporter<EthereumKeyStore> EthereumKeyImporter;
typedef FileImporter<StealthKeyStore> StealthKeyImporter;


}
