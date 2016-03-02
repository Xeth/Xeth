#include "DataBaseDirectory.hpp"
#include <QDebug>

#ifdef __WINDOWS_OS__
#include <shlobj.h>
#endif

namespace Xeth{

DataBaseDirectory::DataBaseDirectory(const Settings &settings, bool create)
{
    if(settings.has("database"))
    {
        _path = boost::filesystem::absolute(settings.get("database"));
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


DataBaseDirectory::DataBaseDirectory(const char *path, bool create) :
    _path(path ? ResolvePath(path) : GetDefaultPath())
{
    if(create)
    {
        createIfNotExists();
    }
}

DataBaseDirectory::DataBaseDirectory(const boost::filesystem::path &path, bool create) :
    _path(path)
{
    if(create)
    {
        createIfNotExists();
    }
}


DataBaseDirectory::DataBaseDirectory(bool create) :
    _path(GetDefaultPath())
{
    if(create)
    {
        createIfNotExists();
    }
}

const boost::filesystem::path & DataBaseDirectory::getPath() const
{
    return _path;
}

std::string DataBaseDirectory::toString() const
{
    return _path.string();
}

void DataBaseDirectory::createIfNotExists()
{
    if(!createIfNotExistsNoThrow())
    {
        std::stringstream stream;
        stream<<"failed to create directory : "<<_path;
        throw std::runtime_error(stream.str());
    }
}

bool DataBaseDirectory::createIfNotExistsNoThrow()
{

    if(!boost::filesystem::exists(_path))
    {
        return boost::filesystem::create_directories(_path);
    }

    return true;
}

boost::filesystem::path DataBaseDirectory::GetDefaultPath()
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
        path = appdata
    }
    else
    {
        path = getenv("HOMEPATH");
    }
    path += "\\Xeth";
#endif
    return path;
}

boost::filesystem::path DataBaseDirectory::ResolvePath(const char *path)
{
    return boost::filesystem::absolute(path);
}


}

