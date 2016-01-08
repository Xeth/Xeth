#pragma once

#include <QString>

namespace Xeth{


class AddressValidator
{
    public:


        bool validateAddress(const QString &);
        bool validateStealth(const QString &);

};




}
