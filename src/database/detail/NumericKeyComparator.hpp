#pragma once

#include <leveldb/db.h>
#include <leveldb/comparator.h>
#include <leveldb/slice.h>


namespace Xeth{


template<typename Value>
class NumericKeyComparator : public leveldb::Comparator
{
    public:
        int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const;
        int Compare(Value a, Value b) const;
        const char* Name() const;
        void FindShortestSeparator(std::string*, const leveldb::Slice&) const;
        void FindShortSuccessor(std::string*) const;
};


}

#include "NumericKeyComparator.ipp"
