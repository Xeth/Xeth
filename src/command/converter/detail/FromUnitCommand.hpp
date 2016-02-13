#pragma once 

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <QVariant>
#include <QVariantMap>

namespace Xeth{


template<uint64_t unit>
class FromUnitCommand
{
    public:
        QVariant operator()(const QVariant &);
};



}

#include "FromUnitCommand.ipp"
