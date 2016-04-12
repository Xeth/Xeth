#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"

#include "types/EthereumKey.hpp"

#include "detail/GenericChangePasswordCommand.hpp"
#include "detail/ChangeEthereumKeyPasswordOperation.hpp"
#include "detail/ChangeStealthKeyPasswordOperation.hpp"
#include "detail/StealthRedeemKeyFactory.hpp"

namespace Xeth{


class ChangeKeyPasswordCommand 
{
    public:
        ChangeKeyPasswordCommand(DataBase &);
        QVariant operator()(const QVariantMap &);

    private:
        bool changeEthereumKeyPassword(const QString &, const QString &, const QString &);
        bool changeStealthKeyPassword(const QString &, const QString &, const QString &);

    private:
        DataBase &_database;
};


class ChangeEthereumKeyPasswordCommand : 
    public GenericChangePasswordCommand<EthereumKeyStore, ChangeEthereumKeyPasswordOperation>
{
    public:
        typedef GenericChangePasswordCommand<EthereumKeyStore, ChangeEthereumKeyPasswordOperation> Base;

    public:
        ChangeEthereumKeyPasswordCommand(DataBase &);
        bool execute(const QString &address, const QString &password, const QString &newPassword);

    private:
        DataBase & _database;
};


class ChangeStealthKeyPasswordCommand : 
    public GenericChangePasswordCommand<StealthKeyStore, ChangeStealthKeyPasswordOperation>
{
    public:
        typedef GenericChangePasswordCommand<StealthKeyStore, ChangeStealthKeyPasswordOperation> Base;

    public:
        ChangeStealthKeyPasswordCommand(DataBase &);

};



}
