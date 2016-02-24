#include "ImportEthereumKeyCommand.hpp"

namespace Xeth{


ImportEthereumKeyCommand::ImportEthereumKeyCommand(DataBase &database, Synchronizer &synchronizer) :
    Base(database.getEthereumKeys(), synchronizer)
{}



}
