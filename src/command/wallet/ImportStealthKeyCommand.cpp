#include "ImportStealthKeyCommand.hpp"

namespace Xeth{


ImportStealthKeyCommand::ImportStealthKeyCommand(DataBase &database, Synchronizer &synchronizer) :
    Base(database.getStealthKeys(), synchronizer)
{}


}
