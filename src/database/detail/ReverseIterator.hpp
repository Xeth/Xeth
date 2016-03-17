#pragma once

#include <boost/iterator/iterator_adaptor.hpp>


namespace  Xeth {



template<class Iterator>
class ReverseIterator :
        public boost::iterator_adaptor
        <
            ReverseIterator<Iterator>,
            Iterator,
            typename Iterator::ValueType,
            boost::bidirectional_traversal_tag,
            typename Iterator::RefernceType
        >
{
    public:
        typedef boost::iterator_adaptor
        <
            ReverseIterator<Iterator>,
            Iterator,
            typename Iterator::ValueType,
            boost::bidirectional_traversal_tag,
            typename Iterator::RefernceType
        > Base;

    public:
        ReverseIterator(const Iterator &);
        ReverseIterator();

        void increment();
        void decrement();
};


}

#include "ReverseIterator.ipp"
