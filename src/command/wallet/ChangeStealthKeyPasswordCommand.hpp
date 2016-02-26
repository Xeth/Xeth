#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "types/EthereumKey.hpp"
#include "database/DataBase.hpp"

#include "detail/GenericChangePasswordCommand.hpp"
#include "detail/ChangeStealthKeyPasswordOperation.hpp"



namespace Xeth{


class ChangeStealthKeyPasswordCommand : 
    public GenericChangePasswordCommand<StealthKeyStore, ChangeStealthKeyPasswordOperation>
{
    public:
        typedef GenericChangePasswordCommand<StealthKeyStore, ChangeStealthKeyPasswordOperation> Base;

    public:
        ChangeStealthKeyPasswordCommand(DataBase &);

};


}
