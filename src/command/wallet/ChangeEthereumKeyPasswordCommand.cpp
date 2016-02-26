#include "ChangeEthereumKeyPasswordCommand.hpp"


namespace Xeth{


ChangeEthereumKeyPasswordCommnad::ChangeEthereumKeyPasswordCommnad(DataBase &database) :
    Base(database.getEthereumKeys())
{}





}
