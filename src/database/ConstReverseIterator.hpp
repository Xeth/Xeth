#pragma once

#include <boost/iterator/iterator_adaptor.hpp>

#include "ConstIterator.hpp"


namespace  Xeth {



template<class Decoder, class Value>
class ConstReverseIterator :
        public boost::iterator_adaptor
        <
            ConstReverseIterator<Decoder, Value>,
            ConstIterator<Decoder, Value>,
            Value,
            boost::bidirectional_traversal_tag,
            Value
        >
{
    public:
        typedef boost::iterator_adaptor
        <
            ConstReverseIterator<Decoder, Value>,
            ConstIterator<Decoder, Value>,
            Value,
            boost::bidirectional_traversal_tag,
            Value
        > Base;

    public:
        ConstReverseIterator(const ConstIterator<Decoder, Value> &);
        ConstReverseIterator(const boost::shared_ptr<leveldb::Iterator> &);
        ConstReverseIterator(bool);

        void increment();
        void decrement();
};


}

#include "ConstReverseIterator.ipp"
