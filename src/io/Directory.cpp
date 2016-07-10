#include "Directory.hpp"
#include <QDebug>

#ifdef __WINDOWS_OS__
#include <shlobj.h>
#endif

namespace Xeth{

Directory::Directory(const Settings &settings, bool create)
{
    if(settings.has("datadir"))
    {
        _path = boost::filesystem::absolute(settings.get("datadir"));
    }
    else
    {
        _path = GetDefaultPath();
    }

    if(settings.get<bool>("testnet", false))
    {
        _path /= "testnet";
    }

    if(create)
    {
        createIfNotExists();
    }
}


Directory::Directory(const char *path, bool create) :
    _path(path ? ResolvePath(path) : GetDefaultPath())
{
    if(create)
    {
        createIfNotExists();
    }
}

Directory::Directory(const boost::filesystem::path &path, bool create) :
    _path(path)
{
    if(create)
    {
        createIfNotExists();
    }
}


Directory::Directory(bool create) :
    _path(GetDefaultPath())
{
    if(create)
    {
        createIfNotExists();
    }
}

const Directory::Path & Directory::getPath() const
{
    return _path;
}

std::string Directory::toString() const
{
    return _path.string();
}

void Directory::createIfNotExists()
{
    if(!createIfNotExistsNoThrow())
    {
        std::stringstream stream;
        stream<<"failed to create directory : "<<_path;
        throw std::runtime_error(stream.str());
    }
}

bool Directory::createIfNotExistsNoThrow()
{

    if(!boost::filesystem::exists(_path))
    {
        return boost::filesystem::create_directories(_path);
    }

    return true;
}

boost::filesystem::path Directory::GetDefaultPath()
{
    std::string path;
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

boost::filesystem::path Directory::ResolvePath(const char *path)
{
    return boost::filesystem::absolute(path);
}


}

