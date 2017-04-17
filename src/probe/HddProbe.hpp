#pragma once


#include "Probe.hpp"


namespace Xeth{



class HddProbe : public Probe
{
    public:
        ~HddProbe();
        bool operator()(const Settings &) const;
};


}
