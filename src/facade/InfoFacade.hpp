#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QString>
#include <QtConcurrent>


#include "../version.hpp"
#include "command/info/GetClientVersionCommand.hpp"
#include "command/info/GetLastReleaseInfoCommand.hpp"
#include "command/Invoker.hpp"
#include "Notifier.hpp"


namespace Xeth{


class InfoFacade : public QObject
{
    Q_OBJECT

    public:
        InfoFacade(const Settings &, Notifier &, Invoker<Notifier> &);
        Q_INVOKABLE QString  getVersion() const;
        Q_INVOKABLE QVariant getClientVersion() const;
        Q_INVOKABLE QVariant getClientVersionNumber() const;
        Q_INVOKABLE QVariant getLatestReleaseInfo() const;
        Q_INVOKABLE QObject * getLatestReleaseInfoAsync() const;
        Q_INVOKABLE QString getNewerClientVersion() const;
        Q_INVOKABLE QString getNewerXethVersion() const;

        void checkVersion();
        void checkVersionAsync();

    private:
        bool isNewVersion(const QString &, const QString &);
        void checkClientVersion(const QJsonObject &);
        void checkXethVersion(const QJsonObject &);
        qulonglong normalizeVersionNumber(const QString &);


    private:
        const Settings &_settings;
        Notifier &_notifier;
        Invoker<Notifier> &_invoker;
        QString _newerXethVersion;
        QString _newerClientVersion;
};


}
