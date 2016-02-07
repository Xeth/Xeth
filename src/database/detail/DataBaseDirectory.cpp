#include "DataBaseDirectory.hpp"

namespace Xeth{

DataBaseDirectory::DataBaseDirectory(const char *path, bool create) :
    _path(path ? ResolvePath(path) : GetDefaultPath())
{
    qDebug()<<"Creating from path";
    if(create)
    {
        createIfNotExists();
    }
}


DataBaseDirectory::DataBaseDirectory(bool create) :
    _path(GetDefaultPath())
{
    qDebug()<<"creating default";
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
    qDebug()<<"creating...";
    if(!createIfNotExistsNoThrow())
    {
        std::stringstream stream;
        stream<<"failed to create directory : "<<_path;
        throw std::runtime_error(stream.str());
    }
    qDebug()<<"created";
}

bool DataBaseDirectory::createIfNotExistsNoThrow()
{
    qDebug()<<"checking path : "<<_path.c_str();
    boost::filesystem::path path(_path);

    if(!boost::filesystem::exists(path))
    {
        qDebug()<<"creating directory : "<<_path.c_str();
        return boost::filesystem::create_directory(path);
    }

    return true;
}

std::string DataBaseDirectory::GetDefaultPath()
{
    qDebug()<<"get default path";
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

    qDebug()<<"resolving path";
//    boost::filesystem::path result = boost::filesystem::canonical(boost::filesystem::path(path));
    boost::filesystem::path result =  boost::filesystem::absolute(path);
    qDebug()<<"is complete  : "<<result.is_complete();
    return result.string() + "/";
}


}

