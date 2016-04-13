#pragma once

#include <string>
#include <algorithm>


namespace Xeth{


class HexAddressNormalizer
{
    public:
        std::string operator()(const std::string &) const;
        std::string normalize(const std::string &) const;

};


}
