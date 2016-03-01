#pragma once 

#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/gmp.hpp>

#include <QVariant>
#include <QVariantMap>

namespace Xeth{


template<size_t unit>
class FromUnitCommand
{
    public:
        QVariant operator()(const QVariant &);
};



}

#include "FromUnitCommand.ipp"
