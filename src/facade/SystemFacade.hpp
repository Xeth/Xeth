#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QString>
#include <QtConcurrent>


#include "../version.hpp"
#include "Notifier.hpp"

#include "command/info/GetClientVersionCommand.hpp"
#include "command/info/GetLastReleaseInfoCommand.hpp"
#include "command/Invoker.hpp"

#include "probe/SystemProber.hpp"
#include "probe/HddProbe.hpp"


namespace Xeth{


class SystemFacade : public QObject
{
    Q_OBJECT

    public:
        SystemFacade(const Settings &, Notifier &, Invoker<Notifier> &);

        Q_INVOKABLE QString  getVersion() const;
        Q_INVOKABLE QVariant getClientVersion() const;
        Q_INVOKABLE QVariant getClientVersionNumber() const;
        Q_INVOKABLE QVariant getLatestReleaseInfo() const;
        Q_INVOKABLE QObject * getLatestReleaseInfoAsync() const;
        Q_INVOKABLE QString getNewerClientVersion() const;
        Q_INVOKABLE QString getNewerXethVersion() const;

        Q_INVOKABLE QVariant updateLatestReleaseInfo();

        void fetchLatestReleaseData();
        void fetchLatestReleaseDataAsync();

    signals:
        void Error(const QString &) const;
        void Warning(const QString &) const;
        void Success() const;

    private slots:
        void emitError(const QString &);
        void emitWarning(const QString &);
        void emitSuccess();

    private:
        bool isNewVersion(const QString &, const QString &);
        void checkClientVersion(const QJsonObject &);
        void checkXethVersion(const QJsonObject &);
        qulonglong normalizeVersionNumber(const QString &);


    private:
        const Settings &_settings;
        Notifier &_notifier;
        Invoker<Notifier> &_invoker;
        SystemProber _prober;
        QJsonObject _latestData;
        QString _newerXethVersion;
        QString _newerClientVersion;
};


}
