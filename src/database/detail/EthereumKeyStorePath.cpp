#include "EthereumKeyStorePath.hpp"


namespace Xeth{

EthereumKeyStorePath::EthereumKeyStorePath(const Settings &settings)
{
    if(!settings.has("attach"))
    {
        _path = GetDefaultPath();
    }
    else
    {
        _path = MakePath(settings.get("attach"));
    }
}



EthereumKeyStorePath::EthereumKeyStorePath(const std::string &path) :
    _path(MakePath(path))
{}



EthereumKeyStorePath::EthereumKeyStorePath() :
    _path(GetDefaultPath())
{}


std::string EthereumKeyStorePath::GetDefaultPath()
{
    return MakePath(Ethereum::Connector::DefaultGethPath::RootDirectory());
}


std::string EthereumKeyStorePath::MakePath(const std::string &dir)
{
    boost::filesystem::path path = boost::filesystem::absolute(dir);
    path /= "keystore";
    return path.string();
}


const std::string & EthereumKeyStorePath::toString() const
{
    return _path;
}


}
