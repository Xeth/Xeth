#pragma once

#include "RangeIterator.hpp"


namespace Xeth{



template<class Store>
class StoreRange
{
    public:
        typedef RangeIterator<typename Store::Iterator, typename Store::DataType> Iterator;

    public:

        StoreRange(Store &);

        void setLimit(size_t);
        void setOffset(size_t);

        Iterator begin() const;
        Iterator end() const;


    private:
        Store &_store;
        size_t _limit;
        size_t _offset;
};



}

#include "StoreRange.ipp"
