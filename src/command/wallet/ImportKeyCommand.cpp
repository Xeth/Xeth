#include "ImportKeyCommand.hpp"

namespace Xeth{


ImportKeyCommand::ImportKeyCommand(DataBase &database ) :
    GenericImportKeyCommand<EthereumKeyStore>(database.getEthereumKeys())
{}



}
