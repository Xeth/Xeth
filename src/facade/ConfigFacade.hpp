#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QString>

#include "database/DataBase.hpp"
#include "Notifier.hpp"

#include "command/Invoker.hpp"
#include "command/config/AddConfigCommand.hpp"
#include "command/config/GetConfigCommand.hpp"


namespace Xeth{


class ConfigFacade : public QObject
{
    Q_OBJECT

    public:
        ConfigFacade(DataBase &, Invoker<Notifier> &);

        Q_INVOKABLE QVariant set(const QVariantMap &);
        Q_INVOKABLE QVariant get(const QString &);

    signals:
        void Change(const QString &, const QString &) const;

    private slots:
        void emitChange(const QString &, const QString &);

    private:
        DataBase &_database;
        Invoker<Notifier> &_invoker;
};


}
