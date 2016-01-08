#pragma once

#include <leveldb/db.h>

#include <boost/shared_ptr.hpp>
#include <boost/iterator/iterator_facade.hpp>


namespace Xeth{

template<class Decoder, class Value>
class ConstIterator :
        public boost::iterator_facade
        <
            ConstIterator<Decoder, Value>,
            Value,
            boost::bidirectional_traversal_tag,
            Value
        >
{
    public:
        ConstIterator(const boost::shared_ptr<leveldb::Iterator> &);
        ConstIterator(bool);

        void increment();
        void decrement();

        Value dereference() const;
        bool equal(const ConstIterator &) const;

    private:
        Decoder _decoder;
        boost::shared_ptr<leveldb::Iterator> _handle;
        bool _valid;

};


}

#include "ConstIterator.ipp"
