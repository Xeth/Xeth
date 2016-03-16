#include "EthereumKeyStorePath.hpp"


namespace Xeth{

EthereumKeyStorePath::EthereumKeyStorePath(const Settings &settings)
{
    Ethereum::Connector::Network net = settings.get("testnet", false) ? Ethereum::Connector::Test_Net : Ethereum::Connector::Main_Net;
    boost::filesystem::path  path = boost::filesystem::absolute(settings.has("attach")? settings.get("attach") : Ethereum::Connector::Path::GethRootPath(net).toString());
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
    return MakePath(Ethereum::Connector::Path::GethRootPath().toString());
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
