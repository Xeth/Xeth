#include "ExportEthereumKeyCommand.hpp"


namespace Xeth{


ExportEthereumKeyCommand::ExportEthereumKeyCommand(const DataBase &database ) :
    GenericExportKeyCommand<EthereumKeyStore>(database.getEthereumKeys())
{}



}
