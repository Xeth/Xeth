#pragma once 

#include <string>
#include <QString>


namespace Xeth{


template<class Key, class Unlocker>
class GenericKeyValidator
{
    public:
        bool operator()(Key &, const QString &) const;
        bool operator()(Key &, const std::string &password) const;
        bool operator()(Key &, const char *) const;

};

}

#include "GenericKeyValidator.ipp"
