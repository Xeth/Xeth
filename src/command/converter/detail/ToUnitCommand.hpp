#pragma once 

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>

#include <QVariant>
#include <QVariantMap>

namespace Xeth{


template<uint64_t unit>
class ToUnitCommand
{
    public:
        QVariant operator()(const QVariant &);
};



}

#include "ToUnitCommand.ipp"
