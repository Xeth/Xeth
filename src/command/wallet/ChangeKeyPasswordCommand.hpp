#pragma once 

#include <QVariant>
#include <QVariantMap>

#include "database/DataBase.hpp"

#include "ChangeEthereumKeyPasswordCommand.hpp"
#include "ChangeStealthKeyPasswordCommand.hpp"


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



}
