#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "types/EthereumKey.hpp"
#include "database/DataBase.hpp"

#include "detail/GenericChangePasswordCommand.hpp"
#include "detail/ChangeEthereumKeyPasswordOperation.hpp"



namespace Xeth{


class ChangeEthereumKeyPasswordCommand : 
    public GenericChangePasswordCommand<EthereumKeyStore, ChangeEthereumKeyPasswordOperation>
{
    public:
        typedef GenericChangePasswordCommand<EthereumKeyStore, ChangeEthereumKeyPasswordOperation> Base;

    public:
        ChangeEthereumKeyPasswordCommand(DataBase &);

};


}
