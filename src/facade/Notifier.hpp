#pragma once

#include <QObject>
#include <QString>
#include <QVariant>
#include <QVariantMap>
#include <QJsonObject>

#include "database/DataBase.hpp"
#include "synchronizer/Synchronizer.hpp"

namespace Xeth{


class Notifier : public QObject
{
    Q_OBJECT
    public:

        Notifier();

    public slots:
        void emitObjectError(const QString &context, const QString &uri, const QString &msg);
        void emitError(const QString &context, const QString &msg);
        void emitError(const QString &);
        void emitMessage(const QString &);
        void emitReady();


        void emitData(const QString &context, const QString &uri, const QString &key, const QVariant &value);
        void emitData(const QString &context, const QString &key, const QVariant &value);

    signals:
        void Ready() const;
        void Error(const QVariantMap &) const;
        void Message(const QString &) const;
        void Data(const QVariantMap &) const;

};


}
