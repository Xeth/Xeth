#pragma once


#include <boost/iterator/iterator_adaptor.hpp>


namespace Xeth{


template<class Iterator, class Value>
class RangeIterator :
    public boost::iterator_adaptor
        <
            RangeIterator<Iterator, Value>,
            Iterator,
            Value,
            boost::forward_traversal_tag,
            Value
        >
{
    public:
        typedef boost::iterator_adaptor
            <
                RangeIterator<Iterator, Value>,
                Iterator,
                Value,
                boost::forward_traversal_tag,
                Value
            > Base;
    public:
        RangeIterator(const Iterator &, size_t limit);
        RangeIterator();

        void increment();

    private:
        size_t _limit;
        size_t _offset;

};


}

#include "RangeIterator.ipp"
