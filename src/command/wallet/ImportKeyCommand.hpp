#pragma once

#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"
#include "facade/Notifier.hpp"

#include "conf/Settings.hpp"
#include "process/EthProcessInitializer.hpp"
#include "io/JsonReader.hpp"


#include "detail/GenericImportKeyCommand.hpp"


namespace Xeth{


class ImportKeyCommand
{
    public:
        ImportKeyCommand(const Settings &, DataBase &, Synchronizer &, Notifier &);

        QVariant operator()(const QVariantMap &);


    private:
        bool importStealthKey(const QString &path, const QString &password, QString &address);
        bool importEthereumKey(const QString &path, const QString &password, QString &address);
        bool importPresaleKey(const QString &path, const QString &password, QString &address);


    private:
        const Settings &_settings;
        DataBase &_database;
        Synchronizer &_synchronizer;
        Notifier &_notifier;

};


class ImportEthereumKeyCommand : public GenericImportKeyCommand<EthereumKeyImporter>
{
    public:
        typedef GenericImportKeyCommand<EthereumKeyImporter> Base;

    public:
        ImportEthereumKeyCommand(DataBase &db, Synchronizer &);

};


class ImportPresaleKeyCommand
{
    public:
        ImportPresaleKeyCommand(const Settings &, Synchronizer &, DataBase &);

        QVariant operator()(const QVariantMap &);

        bool import(const QVariantMap &, QString &address);
        bool import(const QString &path, const QString &password, QString &address);

    private:
        const Settings &_settings;
        Synchronizer &_synchronizer;
        DataBase &_database;
};


class ImportStealthKeyCommand : public GenericImportKeyCommand<StealthKeyImporter>
{
    public:
        typedef GenericImportKeyCommand<StealthKeyImporter> Base;

    public:
        ImportStealthKeyCommand(DataBase &db, Synchronizer &);

};

}
