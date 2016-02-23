#include "GenerateEthereumKeyCommand.hpp"

namespace Xeth{


GenerateEthereumKeyCommand::GenerateEthereumKeyCommand(DataBase &database, Synchronizer &synchronizer):
    Base(database.getEthereumKeys(), synchronizer)
{}


}
