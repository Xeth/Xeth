#include "KeySerializer.hpp"

namespace Xeth{


leveldb::Slice KeySerializer<char *>::operator()(const char *key) const
{
    return leveldb::Slice(key);
}


leveldb::Slice KeySerializer<unsigned char *>::operator()(const unsigned char *key) const
{
    return leveldb::Slice((const char *)key);
}


leveldb::Slice KeySerializer<std::string>::operator()(const std::string &key) const
{
    return leveldb::Slice(key);
}


}
