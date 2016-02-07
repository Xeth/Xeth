#include "ImportKeyCommand.hpp"

namespace Xeth{


ImportKeyCommand::ImportKeyCommand(DataBase &database, Synchronizer &synchronizer) :
    Base(database.getEthereumKeys(), synchronizer)
{}



}
