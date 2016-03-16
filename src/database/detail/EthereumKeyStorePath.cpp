#include "EthereumKeyStorePath.hpp"

#ifdef __WINDOWS_OS__
#include <shlobj.h>
#endif

namespace Xeth{

EthereumKeyStorePath::EthereumKeyStorePath(const Settings &settings)
{
    boost::filesystem::path  path = boost::filesystem::absolute(settings.has("keystore")? settings.get("keystore") : GetDefaultPath(settings.get("testnet", false)));
    _path = MakePath(path);
}



EthereumKeyStorePath::EthereumKeyStorePath(const std::string &path) :
    _path(MakePath(path))
{}



EthereumKeyStorePath::EthereumKeyStorePath() :
    _path(GetDefaultPath())
{}


std::string EthereumKeyStorePath::GetDefaultPath(bool testnet)
{
    boost::filesystem::path path;
#if  defined(__APPLE_OS__)
    path = getenv("HOME");
    path /= "Library/Ethereum";
#elif defined(__LINUX_OS__)
    path = getenv("HOME");
    path /= ".ethereum";
#elif defined(__WINDOWS_OS__)
    char appdata[1024] = "";
    if (SHGetSpecialFolderPathA(NULL, appdata, CSIDL_APPDATA, true))
    {
        path = appdata;
    }
    else
    {
        path = getenv("HOMEPATH");
    }
    path /= "Ethereum";
#endif
    if(testnet)
    {
        path /= "testnet";
    }

    return MakePath(path);
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
