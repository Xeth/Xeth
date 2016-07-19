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
    return insert(makeFileName(key).c_str(), key);
}


bool EthereumKeyStore::replace(const EthereumKey &key)
{
    std::string address = key.getAddress().toString();
    Iterator it = find(address.c_str());
    std::string path;
    if(it!=end())
    {
        path = it.path().filename().string();
    }
    else
    {
        path = makeFileName(key);
    }

    if(Base::replace(path.c_str(), key))
    {
        emit Key(QString(address.c_str()));
        return true;
    }
    return false;
}


bool EthereumKeyStore::replace(const EthereumKey &key, time_t time)
{
    return replaceNoCheck(makeFileName(key, time).c_str(), key);
}


void EthereumKeyStore::touch(const char *address) const
{
    Iterator it = find(address);
    if(it!=end())
    {
        emit Key(it->getAddress().toString().c_str());
    }
}


bool EthereumKeyStore::replaceNoCheck(const char *filename, const EthereumKey &key)
{
    if(Base::replace(filename, key))
    {
        emit Key(QString(key.getAddress().toString().c_str()));
        return true;
    }
    return false;
}



bool EthereumKeyStore::insert(const char *id, const EthereumKey &key)
{
    Iterator it = find(key.getAddress().toString().c_str());
    if(it!=end())
    {
        return false;
    }

    if(Base::insert(id, key))
    {
        emit Key(QString(key.getAddress().toString().c_str()));
        return true;
    }
    return false;
}

bool EthereumKeyStore::insert(const EthereumKey &key, time_t time)
{
    return insert(makeFileName(key, time).c_str(), key);
}

bool EthereumKeyStore::validateId(const std::string &id, const EthereumKey &key)
{
    boost::regex regex("UTC\\-\\-.+\\-\\-([0-9a-fA-F]+?).*$", boost::regex::icase);
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

    boost::regex regex(pattern, boost::regex::icase);
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

std::string EthereumKeyStore::makeFileName(const EthereumKey &key, time_t time) const
{
    return makeFileName(key, boost::posix_time::ptime(boost::gregorian::date(1970,1,1)) + boost::posix_time::seconds(static_cast<long>(time)));
}

std::string EthereumKeyStore::makeFileName(const EthereumKey &key, const boost::posix_time::ptime &time) const
{
    std::string path = "UTC--";
    path += boost::posix_time::to_iso_extended_string(time);
    path += "--";
    path += key.getAddress().toString();
    std::replace(path.begin(), path.end(), ':','-');
    return path;
}




}
