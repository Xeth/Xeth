#include "ExportStealthKeyCommand.hpp"


namespace Xeth{


ExportStealthKeyCommand::ExportStealthKeyCommand(const DataBase &database ) :
    GenericExportKeyCommand<StealthKeyStore>(database.getStealthKeys())
{}



}
