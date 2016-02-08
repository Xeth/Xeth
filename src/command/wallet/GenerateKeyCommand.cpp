#include "GenerateKeyCommand.hpp"

namespace Xeth{


GenerateKeyCommand::GenerateKeyCommand(DataBase &database, Synchronizer &synchronizer):
    Base(database.getEthereumKeys(), synchronizer)
{}


}
