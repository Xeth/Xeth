#pragma once

#include <QObject>
#include <QJsonObject>

#include "detail/LevelDbStore.hpp"

namespace Xeth{


class AddressBookDataSerializer : public DataSerializer<QJsonObject>
{
    public:
        typedef DataSerializer<QJsonObject> Base;

    public:
        QJsonObject operator()(const char *, const char *) const;
        bool operator()(const char *, const char *, QJsonObject &) const;
        std::string operator()(const QJsonObject &) const;
};



class AddressBookStore : 
    public QObject,
    public LevelDbStore<QJsonObject, AddressBookDataSerializer>
{

    Q_OBJECT
    public:
        typedef LevelDbStore<QJsonObject, AddressBookDataSerializer> Base;
        typedef Base::Iterator Iterator;
        typedef Base::ReverseIterator ReverseIterator;
        typedef Base::DataType DataType;

    public:
        AddressBookStore();
        AddressBookStore(const std::string &);
        AddressBookStore(const boost::filesystem::path &);

        bool insert(const char *, const char *);
        bool insert(const char *, const QJsonObject &);

    signals:
        void NewItem(const QJsonObject &) const;
};





}
