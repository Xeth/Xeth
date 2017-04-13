#include "ConfigStore.hpp"


namespace Xeth{


ConfigStore::ConfigStore()
{}

ConfigStore::ConfigStore(const char *path) :
    Base(path)
{}

ConfigStore::ConfigStore(const std::string &path) :
    Base(path)
{}

ConfigStore::ConfigStore(const boost::filesystem::path &path) :
    Base(path)
{}


void ConfigStore::insert(const QString &key, const QString &value)
{
    replace(key.toStdString().c_str(), value);
    emit Change(key, value);
}


void ConfigStore::insert(const char *key, const QString &value)
{
    replace(key, value);
    emit Change(key, value);
}


bool ConfigStore::has(const char *name) const
{
    return Base::has(name);
}


QString ConfigStore::get(const char *name) const
{
    return Base::get(name);
}




}
