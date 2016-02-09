#include "DataBaseDirectory.hpp"

namespace Xeth{

DataBaseDirectory::DataBaseDirectory(const char *path, bool create) :
    _path(path ? ResolvePath(path) : GetDefaultPath())
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

const std::string & DataBaseDirectory::getPath() const
{
    return _path;
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
    boost::filesystem::path path(_path);

    if(!boost::filesystem::exists(path))
    {
        return boost::filesystem::create_directory(path);
    }

    return true;
}

std::string DataBaseDirectory::GetDefaultPath()
{
    std::string path;
#if  defined(__APPLE__)
    path = getenv("HOME");
    path += "/Library/Xeth/";
#elif defined(__linux__)
    path = getenv("HOME");
    path += "/.xeth/";
#elif defined(__MINGW32__)
    path = getenv("HOMEPATH");
    path += "\\AppData\\Roaming\\Xeth\\";
#endif
    return path;
}

std::string DataBaseDirectory::ResolvePath(const char *path)
{
    boost::filesystem::path result =  boost::filesystem::absolute(path);
    return result.string() + "/";
}


}

