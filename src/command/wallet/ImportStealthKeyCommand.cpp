#include "ImportStealthKeyCommand.hpp"

namespace Xeth{


ImportStealthKeyCommand::ImportStealthKeyCommand(DataBase &database ) :
    GenericImportKeyCommand<StealthKeyStore>(database.getStealthKeys())
{}



}
