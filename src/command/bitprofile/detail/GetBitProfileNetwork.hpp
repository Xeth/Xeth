#pragma once

#include "bitprofile/Network.hpp"
#include "env/Settings.hpp"


namespace Xeth{


inline BitProfile::Network GetBitprofileNetwork(const Settings &settings)
{
    return settings.get<bool>("testnet", false)?BitProfile::Test_Net:BitProfile::Main_Net;
}



}
