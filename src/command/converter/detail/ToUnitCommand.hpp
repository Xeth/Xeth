#pragma once 

#include <boost/multiprecision/cpp_int.hpp>

#if __HAS_GMP__

#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/gmp.hpp>

#else

#include <boost/multiprecision/cpp_dec_float.hpp>

#endif

#include <QVariant>
#include <QVariantMap>

namespace Xeth{


template<size_t unit>
class ToUnitCommand
{
    public:
        QVariant operator()(const QVariant &);
};



}

#include "ToUnitCommand.ipp"
