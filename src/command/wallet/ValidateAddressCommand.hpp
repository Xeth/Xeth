#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "detail/AddressValidator.hpp"
#include "types/StealthKey.hpp"


namespace Xeth{


class ValidateAddressCommand
{
    public:
        QVariant operator()(const QString &);
        QVariant operator()(const QVariantMap &);

    private:
        bool isHexAddress(const QString &);
        QVariant validateAddress(const QString &, bool checksum);
        QVariant validateHexAddress(const QString &, bool checksum);
        QVariant validateStealthAddress(const QString &, bool checksum);
};


}
