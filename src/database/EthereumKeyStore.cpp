#include "EthereumKeyStore.hpp"
#include <cctype>

namespace Xeth{

EthereumKeyStore::EthereumKeyStore(const std::string &path) : 
    Base(path, "")
{}

EthereumKeyStore::EthereumKeyStore(const boost::filesystem::path &path) : 
    Base(path, "")
{}


bool EthereumKeyStore::insert(const EthereumKey &key) 
{
    if(Base::insert(makeFileName(key).c_str(), key))
    {
        emit NewItem(QString(key.getAddress().toString().c_str()));
        return true;
    }
    return false;
}


bool EthereumKeyStore::replace(const EthereumKey &key)
{
    return Base::replace(makeFileName(key).c_str(), key);
}


bool EthereumKeyStore::replace(const std::string &filename, const EthereumKey &key)
{
    return replace(filename.c_str(), key);
}


bool EthereumKeyStore::replace(const char *filename, const EthereumKey &key)
{
    if(!validateId(filename, key))
    {
        return Base::replace(makeFileName(key).c_str(), key);
    }

    if(Base::replace(filename, key))
    {
        emit NewItem(QString(key.getAddress().toString().c_str()));
        return true;
    }
    return false;
}


bool EthereumKeyStore::insert(const char *id, const EthereumKey &key)
{
    if(!validateId(id, key))
    {
        return Base::insert(makeFileName(key, boost::posix_time::from_time_t(0)).c_str(), key); //creation data unknown
    }
    if(Base::insert(id, key))
    {
        emit NewItem(QString(key.getAddress().toString().c_str()));
        return true;
    }
    return false;
}

bool EthereumKeyStore::insert(const std::string &id, const EthereumKey &key)
{
    return insert(id.c_str(), key);
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
    std::string pattern = "--";
    if(address[0]=='0'&&address[1]=='x')
    {
        address += 2;
    }

    std::string addr = address;
    std::transform(addr.begin(), addr.end(), addr.begin(), ::tolower);

    pattern += addr;
    pattern += '$';

    boost::smatch match;

    boost::regex regex(pattern);
    Iterator it=begin(), e=end();

    for(; it!=e; ++it)
    {
        std::string filename = it.path().filename().string();
        if(boost::regex_search(filename, match, regex))
        {
            //extra check
            EthereumKey key = *it;
            if(it->getAddress().toString() == addr)
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


std::string EthereumKeyStore::makeFileName(const EthereumKey &key) const
{
    return makeFileName(key, boost::posix_time::microsec_clock::universal_time());
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
