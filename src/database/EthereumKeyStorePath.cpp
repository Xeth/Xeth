#include "EthereumKeyStorePath.hpp"

#ifdef __WINDOWS_OS__
#include <shlobj.h>
#endif

namespace Xeth{

EthereumKeyStorePath::EthereumKeyStorePath(const Settings &settings)
{
    if(settings.has("keystore"))
    {
        boost::filesystem::path  path = boost::filesystem::absolute(settings.get("keystore").toStdString() );
        _path = MakePath(path, settings.get("testnet", false));
    }
    else
    {
        _path = GetDefaultPath(settings.get("testnet", false));
    }
}



EthereumKeyStorePath::EthereumKeyStorePath(const std::string &path, bool testnet) :
    _path(MakePath(path, testnet))
{}



EthereumKeyStorePath::EthereumKeyStorePath() :
    _path(GetDefaultPath())
{}


std::string EthereumKeyStorePath::GetDefaultPath(bool testnet)
{
    if(testnet)
    {
        return ApplicationPath::TestnetKeys().toStdString();
    }
    return ApplicationPath::Keys().toStdString();
}


std::string EthereumKeyStorePath::MakePath(const std::string &dir, bool testnet)
{
    boost::filesystem::path path = boost::filesystem::absolute(dir);
    return MakePath(path, testnet);
}

std::string EthereumKeyStorePath::MakePath(boost::filesystem::path &path, bool testnet)
{
    path /= testnet ? "testnet" : "ethereum";
    return path.string();
}


const std::string & EthereumKeyStorePath::toString() const
{
    return _path;
}


}
