#pragma once

#include <leveldb/db.h>

#include <boost/shared_ptr.hpp>
#include <boost/iterator/iterator_facade.hpp>


namespace Xeth{

template<class DataDecoder, class Value, class KeyDecoder, class Key>
class LevelDbIterator :
        public boost::iterator_facade
        <
            LevelDbIterator<DataDecoder, Value, KeyDecoder, Key>,
            Value,
            boost::bidirectional_traversal_tag,
            Value
        >
{
    public:
        typedef Value ValueType;
        typedef Value RefernceType;

    public:
        LevelDbIterator(const boost::shared_ptr<leveldb::Iterator> &);
        LevelDbIterator();

        void increment();
        void decrement();

        std::string keyString() const;
        Value dereference() const;
        bool equal(const LevelDbIterator &) const;

    private:
        DataDecoder _dataDecoder;
        KeyDecoder _keyDecoder;
        boost::shared_ptr<leveldb::Iterator> _handle;
        bool _valid;

};


}

#include "LevelDbIterator.ipp"
