#include "BitProfileSettings.hpp"


namespace Xeth{


BitProfileSettings::BitProfileSettings(const Settings &settings) :
    _net(GetBitprofileNetwork(settings))
{}


BitProfile::Network BitProfileSettings::getNetwork() const
{
    return _net;
}


}
