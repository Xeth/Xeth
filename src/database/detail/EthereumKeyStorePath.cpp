#include "EthereumKeyStorePath.hpp"


namespace Xeth{

EthereumKeyStorePath::EthereumKeyStorePath(const Settings &settings)
{
    boost::filesystem::path  path = boost::filesystem::absolute(settings.has("attach")? settings.get("attach") : GetDefaultPath());

    if(settings.get("testnet", false))
    {
        path /= "testnet";
    }

    _path = MakePath(path);
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
    return MakePath(path);
}

std::string EthereumKeyStorePath::MakePath(boost::filesystem::path &path)
{
    path /= "keystore";
    return path.string();
}


const std::string & EthereumKeyStorePath::toString() const
{
    return _path;
}


}
