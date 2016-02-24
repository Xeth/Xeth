#pragma once

#include <leveldb/slice.h>


namespace Xeth{


template<class Key>
class NumericKeySerializer
{
    public:
        leveldb::Slice operator()(const Key &) const;


};



}

#include "NumericKeySerializer.ipp"
