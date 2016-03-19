#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "detail/AddressValidator.hpp"


namespace Xeth{


class ValidateAddressCommand
{
    public:
        QVariant operator()(const QString &);
};


}
