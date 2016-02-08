#include "GenerateStealthKeyCommand.hpp"

namespace Xeth{


GenerateStealthKeyCommand::GenerateStealthKeyCommand(DataBase &database, Synchronizer &synchronizer):
    Base(database.getStealthKeys(), synchronizer)
{}


}
