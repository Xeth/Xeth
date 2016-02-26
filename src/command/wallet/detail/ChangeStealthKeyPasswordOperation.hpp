#pragma once 

#include <QString>

#include "types/StealthKey.hpp"
#include "types/Cipher.hpp"


namespace Xeth{


class ChangeStealthKeyPasswordOperation
{
    public:
        StealthKey operator()(const StealthKey &, const QString &password, const QString &newPassword);
};


}
