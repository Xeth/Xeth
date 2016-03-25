#pragma once

#include "bitprofile/MasterRegistrar.hpp"
#include "env/Settings.hpp"


namespace Xeth{


inline BitProfile::MasterRegistrar::Network GetBitprofileNetwork(const Settings &settings)
{
    return settings.get<bool>("testnet", false)?BitProfile::MasterRegistrar::Test_Net:BitProfile::MasterRegistrar::Main_Net;
}



}
