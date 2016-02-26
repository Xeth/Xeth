#include "ChangeEthereumKeyPasswordCommand.hpp"


namespace Xeth{


ChangeEthereumKeyPasswordCommand::ChangeEthereumKeyPasswordCommand(DataBase &database) :
    Base(database.getEthereumKeys())
{}





}
