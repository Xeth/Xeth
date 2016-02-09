#include "EthereumKeyStore.hpp"


namespace Xeth{

EthereumKeyStore::EthereumKeyStore(const std::string &path) : 
    Base(path, "")
{}


bool EthereumKeyStore::insert(const EthereumKey &key) 
{

    return Base::insert(makeFileName(key, boost::posix_time::microsec_clock::universal_time()).c_str(), key);
}




bool EthereumKeyStore::insert(const char *id, const EthereumKey &key)
{
    if(!validateId(id, key))
    {
        return Base::insert(makeFileName(key, boost::posix_time::from_time_t(0)).c_str(), key); //creation data unknown
    }
    return Base::insert(id, key);
}

bool EthereumKeyStore::insert(const std::string &id, const EthereumKey &key)
{
    if(!validateId(id, key))
    {
        return Base::insert(makeFileName(key, boost::posix_time::from_time_t(0)).c_str(), key); //creation data unknown
    }
    return Base::insert(id.c_str(), key);
}

bool EthereumKeyStore::validateId(const std::string &id, const EthereumKey &key)
{
    boost::regex regex("UTC\\-\\-.+\\-\\-([0-9a-fA-F]+)$");
    boost::smatch match;

    if (boost::regex_search(id, match, regex))
    {
        return key.getAddress().toString() == match[1];
    }

    return false;
}


EthereumKeyStore::Iterator EthereumKeyStore::find(const char *address) const
{
    std::string pattern = "\\-\\-";
    pattern += address;
    pattern += "$";
    boost::smatch match;

    boost::regex regex(pattern);
    Iterator it=begin(), e=end();

    for(; it!=e; ++it)
    {
        std::string filename = it.path().stem().string();
        if(boost::regex_search(filename, match, regex))
        {
            //extra check
            EthereumKey key = *it;
            if(it->getAddress().toString() == address)
            {
                break;
            }
        }
    }
    return it;
}


EthereumKeyStore::Iterator EthereumKeyStore::find(const Ethereum::Address &address) const
{
    return find(address.toString().c_str());
}


EthereumKey EthereumKeyStore::get(const char *address) const
{
    Iterator it = find(address);
    if(it==end())
    {
        throw std::runtime_error("key not found");
    }
    return *it;
}


std::string EthereumKeyStore::makeFileName(const EthereumKey &key, const boost::posix_time::ptime &time) const
{
    std::string path = "UTC--";
    path += boost::posix_time::to_iso_extended_string(time);
    path += "--";
    path += key.getAddress().toString();
    return path;
}




}
