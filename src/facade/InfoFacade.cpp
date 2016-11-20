
#include "InfoFacade.hpp"

namespace Xeth{


InfoFacade::InfoFacade(const Settings &settings) : 
    _settings(settings)
{}


QString InfoFacade::getVersion() const
{
    return QString(XETH_VERSION);
}


QString InfoFacade::getClientVersion() const
{
    GetClientVersionCommand command(_settings);
    return command();
}

}
