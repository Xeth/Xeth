#pragma once

#include <leveldb/db.h>

#include <boost/shared_ptr.hpp>
#include <boost/iterator/iterator_facade.hpp>


namespace Xeth{

template<class Decoder, class Value>
class LevelDbIterator :
        public boost::iterator_facade
        <
            LevelDbIterator<Decoder, Value>,
            Value,
            boost::bidirectional_traversal_tag,
            Value
        >
{
    public:
        LevelDbIterator(const boost::shared_ptr<leveldb::Iterator> &);
        LevelDbIterator();

        void increment();
        void decrement();

        Value dereference() const;
        bool equal(const LevelDbIterator &) const;

    private:
        Decoder _decoder;
        boost::shared_ptr<leveldb::Iterator> _handle;
        bool _valid;

};


}

#include "LevelDbIterator.ipp"
