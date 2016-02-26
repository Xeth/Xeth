#include "ChangeStealthKeyPasswordCommand.hpp"


namespace Xeth{


ChangeStealthKeyPasswordCommand::ChangeStealthKeyPasswordCommand(DataBase &database) :
    Base(database.getStealthKeys())
{}


}
