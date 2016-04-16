#pragma once 

#include "bitprofile/Network.hpp"
#include "GetBitProfileNetwork.hpp"

namespace Xeth{


class Settings;


class BitProfileSettings
{
    public:
        BitProfileSettings(const Settings &);

        BitProfile::Network getNetwork() const;

    private:
        BitProfile::Network _net;

};



}
