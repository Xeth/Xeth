#pragma once

#include <string>
#include <algorithm>


namespace Xeth{


class HexAddressNormalizer
{
    public:
        std::string operator()(const std::string &) const;
        std::string normalize(const std::string &) const;

        void operator()(const std::string &, std::string &) const;
        void normalize(const std::string &, std::string &) const;
};


}
