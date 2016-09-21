#include "GetVersionCommand.hpp"


namespace Xeth{


QString GetVersionCommand::operator()()
{
    return QString(XETH_VERSION);
}


}
