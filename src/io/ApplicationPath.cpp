#include "ApplicationPath.hpp"

#ifdef __WINDOWS_OS__
#include <shlobj.h>
#endif

namespace  Xeth{


QString ApplicationPath::Vendors()
{
    QString path = QCoreApplication::applicationDirPath();
#if defined(__WINDOWS_OS__)
    path.append("\\vendor\\bin");
#else
    path.append("/vendor/bin");
#endif
    return path;
}


QString ApplicationPath::XethData()
{
    QString path;
#if  defined(__APPLE_OS__)
    path = getenv("HOME");
    path += "/Library/Xeth";
#elif defined(__LINUX_OS__)
    path = getenv("HOME");
    path += "/.xeth";
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
    path += "\\Xeth";
#endif

    return path;
}


QString ApplicationPath::LocalVendors()
{
    QString path = XethData();
#if defined(__WINDOWS_OS__)
    path += "\\vendor\\bin";
#else
    path += "/vendor/bin";
#endif
    return path;
}


QString ApplicationPath::EthereumData()
{
    QString path;
#if  defined(__APPLE_OS__)
    path = getenv("HOME");
    path += "/Library/Ethereum";
#elif defined(__LINUX_OS__)
    path = getenv("HOME");
    path += "/.ethereum";
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
    path += "\\Ethereum";
#endif
    return path;
}


QString ApplicationPath::Keys()
{
    QString path = EthereumData();
#if defined(__WINDOWS_OS__)
    path += "\\keystore\\ethereum";
#else
    path += "/keystore/ethereum";
#endif
    return path;
}


QString ApplicationPath::TestnetKeys()
{
    QString path = EthereumData();
#if defined(__WINDOWS_OS__)
    path += "\\keystore\\testnet";
#else
    path += "/keystore/testnet";
#endif
    return path;
}


QString ApplicationPath::StealthKeys()
{
    QString path = XethData();
#if defined(__WINDOWS_OS__)
    path+="\\keystore";
#else
    path+="/keystore";
#endif
    return path;
}


QString ApplicationPath::TestnetStealthKeys()
{
    QString path = XethData();
#if defined(__WINDOWS_OS__)
    path+="\\testnet\\keystore";
#else
    path+="/testnet/keystore";
#endif
    return path;
}


}
