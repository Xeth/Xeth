#include "ExportKeyCommand.hpp"


namespace Xeth{


ExportKeyCommand::ExportKeyCommand(const DataBase &database ) :
    GenericExportKeyCommand<EthereumKeyStore>(database.getEthereumKeys())
{}



}
