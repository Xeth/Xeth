#pragma once

#include <string>

#include <QJsonDocument>
#include <QJsonObject>

#include <boost/lexical_cast.hpp>

#include "Store.hpp"


namespace Xeth{


class TransactionDataSerializer : public DataSerializer<QJsonObject>
{
    public:
        QJsonObject operator()(const char *, const char *) const;
        bool operator()(const char *, const char *, QJsonObject &) const;

        using DataSerializer::operator(); //for serialization
};




typedef Store<QJsonObject, TransactionDataSerializer> TransactionDataStore;
typedef Store<std::string> TransactionIndexStore;



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


}
