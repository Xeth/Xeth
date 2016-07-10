#include "StealthKeyStore.hpp"

namespace Xeth{

StealthKeyStore::StealthKeyStore(const std::string &path) : 
    Base(path, "skey")
{}

StealthKeyStore::StealthKeyStore(const boost::filesystem::path &path) : 
    Base(path, "skey")
{}


bool StealthKeyStore::replace(const StealthKey &key)
{
    std::string address = makeAddress(key);
    if(Base::replace(address.c_str(), key))
    {
        emit Key(QString(address.c_str()));
        return true;
    }
    return false;
}


bool StealthKeyStore::replace(const StealthKey &key, time_t)
{
    return replace(key);
}


bool StealthKeyStore::insert(const StealthKey &key, time_t)
{
    return insert(key);
}



bool StealthKeyStore::insert(const StealthKey &key) 
{
    std::string address = makeAddress(key);
    if(Base::insert(address.c_str(), key))
    {
        emit Key(QString(address.c_str()));
        return true;
    }
    return false;
}


StealthKey StealthKeyStore::get(const char *address) const
{
    return Base::get(address);
}

StealthKeyStore::Iterator StealthKeyStore::find(const char *address) const
{
    return Base::find(address);
}


StealthKeyStore::Iterator StealthKeyStore::find(const Ethereum::Stealth::Address &address) const
{
    return Base::find(address.toString().c_str());
}


std::string StealthKeyStore::makeAddress(const StealthKey &key) const
{
    Ethereum::Stealth::Address address(key);
    return address.toString();
}





}
