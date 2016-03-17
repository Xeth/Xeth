#pragma once 

#include <leveldb/slice.h>


namespace Xeth{


template<class Key>
class KeySerializer
{
    public:
        leveldb::Slice operator()(const Key &) const;
        std::string toString(const leveldb::Slice &) const;
        Key operator()(const leveldb::Slice &) const;
        Key operator()() const;
};



}

#include "KeySerializer.ipp"
