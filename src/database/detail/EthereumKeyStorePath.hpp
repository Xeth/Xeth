#pragma once 

#include <string>
#include <boost/filesystem.hpp>

#include "ethrpc/transport/Path.hpp"

#include "Settings.hpp"


namespace Xeth{


class EthereumKeyStorePath
{
    public:

        EthereumKeyStorePath(const Settings &);
        const std::string & toString() const;


    private:
        std::string _path;
};



}
