#pragma once

#include <leveldb/db.h>

#include <boost/make_shared.hpp>
#include <boost/filesystem.hpp>
#include <boost/iterator/reverse_iterator.hpp>

#include "LevelDbIterator.hpp"
#include "ReverseIterator.hpp"
#include "DataSerializer.hpp"
#include "KeySerializer.hpp"
#include "NumericKeySerializer.hpp"
#include "NumericKeyComparator.hpp"


namespace Xeth{

class DefaultKeyComparator
{};


template
<
    class Value, 
    class ValueSerializer=Xeth::DataSerializer<Value>, 
    class Key=const char*, 
    class KeySerializer=Xeth::KeySerializer<Key>,
    class KeyComparator = DefaultKeyComparator
>
class LevelDbStore
{
    public:
        typedef LevelDbIterator<ValueSerializer, Value, KeySerializer, Key> Iterator;
        typedef Xeth::ReverseIterator<Iterator> ReverseIterator;
        typedef Value DataType;

    public:
        LevelDbStore();
        LevelDbStore(const char *path);
        LevelDbStore(const std::string &);
        LevelDbStore(const boost::filesystem::path &path);

        ~LevelDbStore();

        template<class String>
        void open(const String &);

        template<class String>
        bool openNoThrow(const String &);

        bool openNoThrow(const boost::filesystem::path &);
        void open(const boost::filesystem::path &);

        void close();

        const std::string &getPath() const;

        Iterator begin() const;
        Iterator end() const;
        Iterator find(const Key &) const;
        bool has(const Key &) const;

        ReverseIterator rbegin() const;
        ReverseIterator rend() const;

        bool contains(const Key &) const;
        bool get(const Key &, Value &) const;
        Value get(const Key &) const;

        bool insert(const Key &, const Value &);
        bool remove(const Key &);
        bool move(const Key &oldKey, const Key &newKey);
        bool replace(const Key &key, const Value &);

    protected:
        bool insert(const leveldb::Slice &, const leveldb::Slice &);
        bool replace(const leveldb::Slice &, const leveldb::Slice &);
        bool move(const leveldb::Slice &, const leveldb::Slice &);
        bool remove(const leveldb::Slice &);

    private:
        Iterator makeIterator(leveldb::Iterator *) const;

        template<class Comparator>
        leveldb::Options makeOptions(const Comparator &);

        leveldb::Options makeOptions(const DefaultKeyComparator &);

        ReverseIterator makeReverseIterator(leveldb::Iterator *) const;

        leveldb::Slice makeKey(const Key &) const;
        std::string makeValue(const Value &) const;


   private:
        KeyComparator _comparator;
        std::string _path;
        leveldb::DB *_db;
};


}

#include "LevelDbStore.ipp"
