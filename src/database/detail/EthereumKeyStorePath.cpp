#include "EthereumKeyStorePath.hpp"


namespace Xeth{

EthereumKeyStorePath::EthereumKeyStorePath(const Settings &settings)
{
    _path = settings.get("attach", "");

    if(!_path.size())
    {
        Ethereum::Connector::DefaultGethPath defaultPath;
        _path = defaultPath.toString();
    }

    _path += boost::filesystem::path::preferred_separator;
    _path += "keystore";

}


const std::string & EthereumKeyStorePath::toString() const
{
    return _path;
}


}
