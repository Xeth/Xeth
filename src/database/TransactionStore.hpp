#pragma once

#include <string>

#include <QJsonDocument>
#include <QJsonObject>

#include <boost/lexical_cast.hpp>

#include "Store.hpp"

namespace Xeth{

class TransactionDataDecoder
{
    public:
        QJsonObject operator()(const char *, const char *) const;
        bool operator()(const char *, const char *, QJsonObject &) const;
        std::string operator ()(const QJsonObject &) const;
};


class TransactionIndexDecoder
{
    public:
        std::string operator ()(const char *, const char *) const;
        bool operator()(const char *, const char *, std::string &) const;
        std::string operator ()(const std::string &) const;
};

typedef Store<TransactionDataDecoder, QJsonObject> TransactionDataStore;
typedef Store<TransactionIndexDecoder, std::string> TransactionIndexStore;



class TransactionStore
{
    public:
        typedef TransactionDataStore::Iterator Iterator;
        typedef TransactionDataStore::ReverseIterator ReverseIterator;
        typedef TransactionDataStore::DataType DataType;


    public:
        TransactionStore();
        TransactionStore(const std::string &path);

        void open(const std::string &);
        bool openNoThrow(const std::string &);

        bool insert(const QJsonObject &);

        QJsonObject get(const char *hash) const;
        Iterator begin() const;
        Iterator end() const;
        Iterator at(int ) const;
        ReverseIterator rbegin() const;
        ReverseIterator rend() const;


    private:
        std::string getNextIndex();

    private:
        TransactionDataStore _dataStore;
        TransactionIndexStore _indexStore;
        size_t _lastIndex;

};


//class TransactionStore
//{
//    public:
//        TransactionStore(const char *chroot);
//        ~TransactionStore();

//        bool add(const TransactionCategory &, const char *hash, const char *src, const char *dest, const BigInt &amount, time_t);
//        bool add(QVariantList::const_iterator begin, QVariantList::const_iterator end);

//        QVariant getByHash(const char *hash);
//        QVariant listByTime(size_t limit, size_t offset);

//    private:
//        std::string getNextIndex();

//    private:
//        leveldb::DB *_txDb;
//        leveldb::DB *_txIndex;
//        uint64_t _lastIndex;

//};

}
