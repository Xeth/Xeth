#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QString>

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
        InfoFacade(const Settings &,  Invoker<Notifier> &);
        Q_INVOKABLE QString  getVersion() const;
        Q_INVOKABLE QVariant getClientVersion() const;
        Q_INVOKABLE QVariant getClientVersionNumber() const;
        Q_INVOKABLE QVariant getLatestReleaseInfo() const;
        Q_INVOKABLE QObject * getLatestReleaseInfoAsync() const;

    private:
        const Settings &_settings;
         Invoker<Notifier> &_invoker;
};


}
