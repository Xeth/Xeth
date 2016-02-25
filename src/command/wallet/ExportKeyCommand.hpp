#pragma once 

#include "database/DataBase.hpp"

#include "ExportEthereumKeyCommand.hpp"
#include "ExportStealthKeyCommand.hpp"


namespace Xeth{


class ExportKeyCommand
{
    public:
        ExportKeyCommand(DataBase &database);
        QVariant operator()(const QVariantMap &);


    private:
        QVariant exportStealthKey(const QString &, const QString &);
        QVariant exportEthereumKey(const QString &, const QString &);

    private:
        DataBase &_database;
};


}
