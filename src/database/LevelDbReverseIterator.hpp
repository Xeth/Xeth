#pragma once

#include <boost/iterator/iterator_adaptor.hpp>

#include "LevelDbIterator.hpp"


namespace  Xeth {



template<class Decoder, class Value>
class LevelDbReverseIterator :
        public boost::iterator_adaptor
        <
            LevelDbReverseIterator<Decoder, Value>,
            LevelDbIterator<Decoder, Value>,
            Value,
            boost::bidirectional_traversal_tag,
            Value
        >
{
    public:
        typedef boost::iterator_adaptor
        <
            LevelDbReverseIterator<Decoder, Value>,
            LevelDbIterator<Decoder, Value>,
            Value,
            boost::bidirectional_traversal_tag,
            Value
        > Base;

    public:
        LevelDbReverseIterator(const LevelDbIterator<Decoder, Value> &);
        LevelDbReverseIterator(const boost::shared_ptr<leveldb::Iterator> &);
        LevelDbReverseIterator();

        void increment();
        void decrement();
};


}

#include "LevelDbReverseIterator.ipp"
