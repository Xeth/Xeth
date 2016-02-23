#pragma once 

#include <leveldb/slice.h>


namespace Xeth{


template<class Key>
class KeySerializer
{
    public:
        leveldb::Slice operator()(const Key &) const;


};


template<>
class KeySerializer<char *>
{
    public:
        leveldb::Slice operator()(const char *) const;
};


template<>
class KeySerializer<unsigned char *>
{
    public:
        leveldb::Slice operator()(const unsigned char *) const;
};


template<>
class KeySerializer<std::string>
{
    public:
        leveldb::Slice operator()(const std::string &) const;
};


}

#include "KeySerializer.ipp"
