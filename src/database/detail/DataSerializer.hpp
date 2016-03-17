#pragma once

#include <string>

#include <boost/lexical_cast.hpp>

#include <QJsonObject>
#include <QJsonDocument>
#include <QString>


namespace Xeth{



template<class Data>
class DataSerializer
{
    public:
        Data operator()(const char *, const char *) const;
        bool operator()(const char *, const char *, Data &) const;
        std::string operator ()(const Data &) const;
};



template<>
class DataSerializer<QJsonObject>
{

    public:

        QJsonObject operator()(const char *, const char *) const;
        bool operator()(const char *, const char *, QJsonObject &) const;
        std::string operator ()(const QJsonObject &) const;
};


template<>
class DataSerializer<QString>
{

    public:

        QString operator()(const char *, const char *) const;
        bool operator()(const char *, const char *, QString &) const;
        std::string operator ()(const QString &) const;
};


template<>
class DataSerializer<std::string>
{
    public:
        std::string operator()(const char *, const char *) const;
        bool operator()(const char *, const char *, std::string &) const;
        std::string operator ()(const std::string &) const;
};


}

#include "DataSerializer.ipp"
