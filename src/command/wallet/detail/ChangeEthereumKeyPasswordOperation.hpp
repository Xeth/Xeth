#pragma once 

#include <QString>

#include "types/EthereumKey.hpp"
#include "types/Cipher.hpp"


namespace Xeth{


class ChangeEthereumKeyPasswordOperation
{
    public:
        EthereumKey operator()(const EthereumKey &, const QString &password, const QString &newPassword);
};


}
