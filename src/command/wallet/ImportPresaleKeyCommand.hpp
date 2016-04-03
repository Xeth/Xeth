#pragma once

#include "env/Settings.hpp"
#include "process/EthProcessInitializer.hpp"
#include "synchronizer/Synchronizer.hpp"
#include "io/JsonReader.hpp"

#include <QVariant>
#include <QVariantMap>


namespace Xeth{



class ImportPresaleKeyCommand
{
    public:
        ImportPresaleKeyCommand(const Settings &, Synchronizer &);

        QVariant operator()(const QVariantMap &);

        bool import(const QVariantMap &, QString &address);
        bool import(const QString &path, const QString &password, QString &address);

    private:
        const Settings &_settings;
        Synchronizer &_synchronizer;
};



}
