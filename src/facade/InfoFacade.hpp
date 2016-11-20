#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantMap>
#include <QString>

#include "../version.hpp"
#include "command/info/GetClientVersionCommand.hpp"


namespace Xeth{


class InfoFacade : public QObject
{
    Q_OBJECT

    public:
        InfoFacade(const Settings &);
        Q_INVOKABLE QString getVersion() const;
        Q_INVOKABLE QString getClientVersion() const;

    private:
        const Settings &_settings;
};


}
