#include "EthereumKeyStore.hpp"


namespace Xeth{

EthereumKeyStore::EthereumKeyStore(const std::string &path) : 
    Base(path, "")
{}


bool EthereumKeyStore::insert(const EthereumKey &key) 
{

    return Base::insert(makeFileName(key.getAddress().toString()).c_str(), key);
}


EthereumKeyStore::Iterator EthereumKeyStore::find(const char *address) const
{
    std::string pattern = "--";
    pattern += address;
    pattern += "$";

    boost::regex regex(pattern);
    Iterator it=begin(), e=end();

    for(; it!=e; ++it)
    {
        std::string filename = it.path().filename().string();
        if(boost::regex_match(filename.c_str(), regex))
        {
            break;
        }
    }
    return it;
}


EthereumKeyStore::Iterator EthereumKeyStore::find(const EthereumAddress &address) const
{
    return find(address.toString().c_str());
}


std::string EthereumKeyStore::makeFileName(const std::string &address) const
{
    std::string path = "UTC--";
    path += boost::posix_time::to_iso_extended_string(boost::posix_time::microsec_clock::universal_time());
    path += "--";
    path += address;
    return path;
}




}
