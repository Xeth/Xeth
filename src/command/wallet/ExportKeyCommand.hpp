#pragma once 

#include "database/DataBase.hpp"
#include "detail/GenericExportKeyCommand.hpp"


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


class ExportEthereumKeyCommand : public GenericExportKeyCommand<EthereumKeyStore>
{
    public:
        ExportEthereumKeyCommand(const DataBase &);

};



class ExportStealthKeyCommand : public GenericExportKeyCommand<StealthKeyStore>
{
    public:
        ExportStealthKeyCommand(const DataBase &);

};



}
