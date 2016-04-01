#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QString>

#include "database/DataBase.hpp"
#include "Notifier.hpp"
#include "Invoker.hpp"

#include "command/config/AddConfigCommand.hpp"
#include "command/config/GetConfigCommand.hpp"


namespace Xeth{


class ConfigFacade : public QObject
{
    Q_OBJECT

    public:
        ConfigFacade(DataBase &, Notifier &);

        Q_INVOKABLE QVariant set(const QVariantMap &);
        Q_INVOKABLE QVariant get(const QString &);


    private:
        DataBase &_database;
        Invoker _invoker;
};


}
