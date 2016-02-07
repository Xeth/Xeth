#pragma once

#include "detail/RangeIterator.hpp"


namespace Xeth{



template<class Store>
class DataRange
{
    public:
        typedef RangeIterator<typename Store::Iterator, typename Store::DataType> Iterator;

    public:

        DataRange(Store &);

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

#include "DataRange.ipp"
