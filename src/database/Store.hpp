#pragma once

#include <leveldb/db.h>

#include <boost/make_shared.hpp>

#include "ConstIterator.hpp"
#include "ConstReverseIterator.hpp"


namespace Xeth{



template<class Decoder, class Value>
class Store
{
    public:
        typedef ConstIterator<Decoder, Value> Iterator;
        typedef ConstReverseIterator<Decoder, Value> ReverseIterator;
        typedef Value DataType;

    public:
        Store();
        Store(const char *path);
        Store(const std::string &);

        ~Store();

        template<class String>
        void open(const String &);

        template<class String>
        bool openNoThrow(const String &);

        void close();

        const std::string &getPath() const;

        Iterator begin() const;
        Iterator end() const;
        Iterator find(const char *) const;

        ReverseIterator rbegin() const;
        ReverseIterator rend() const;

        bool get(const char *, Value &) const;
        Value get(const char *) const;

        bool insert(const char *key, const Value &);
        bool remove(const char *key);
        bool move(const char *oldKey, const char *newKey);
        bool replace(const char *key, const Value &);

    protected:
        bool insert(const char *key, const char *value);
        bool replace(const char *key, const char *value);

    private:
        Iterator makeIterator(leveldb::Iterator *) const;
        ReverseIterator makeReverseIterator(leveldb::Iterator *) const;


   private:
        std::string _path;
        leveldb::DB *_db;
};


}

#include "Store.ipp"
