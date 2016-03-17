#pragma once

#include <leveldb/slice.h>
#include <boost/lexical_cast.hpp>


namespace Xeth{


template<class Key>
class NumericKeySerializer
{
    public:
        leveldb::Slice operator()(const Key &) const;
        std::string toString(const leveldb::Slice &) const;


};



}

#include "NumericKeySerializer.ipp"
