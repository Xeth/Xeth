#pragma once 

#include <QVariant>
#include <QVariantMap>
#include <QDebug>

#include "types/StealthKey.hpp"

namespace Xeth{


class ValidateStealthAddressCommand
{
    public:
        QVariant operator()(const QVariantMap &);
};


}
