#include "StealthKeyStore.hpp"

namespace Xeth{

StealthKeyStore::StealthKeyStore(const std::string &path) : 
    Base(path, "skey")
{}


bool StealthKeyStore::insert(const std::string &id, const StealthKey &key)
{
    //ignore suggested id
    return insert(key);
}

bool StealthKeyStore::insert(const char *id, const StealthKey &key)
{
    //ignore suggested id
    return insert(key);
}


bool StealthKeyStore::insert(const StealthKey &key) 
{
    return Base::insert(makeAddress(key).c_str(), key);
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
