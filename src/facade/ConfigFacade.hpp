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

        QVariant set(const QVariantMap &);
        QVariant get(const QString &);


    private:
        DataBase &_database;
        Invoker _invoker;
};


}
