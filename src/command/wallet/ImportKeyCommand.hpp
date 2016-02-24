#pragma once

#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"

#include "ImportEthereumKeyCommand.hpp"
#include "ImportStealthKeyCommand.hpp"
#include "ImportPresaleKeyCommand.hpp"


namespace Xeth{


class ImportKeyCommand
{
    public:
        ImportKeyCommand(const Settings &, DataBase &, Synchronizer &);

        QVariant operator()(const QVariantMap &);


    private:
        bool importStealthKey(const QString &path, const QString &password, QString &address);
        bool importEthereumKey(const QString &path, const QString &password, QString &address);
        bool importPresaleKey(const QString &path, const QString &password, QString &address);


    private:
        const Settings &_settings;
        DataBase &_database;
        Synchronizer &_synchronizer;

};


}
