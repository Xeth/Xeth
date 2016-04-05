#pragma once 


#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QProcess>

#include "env/Settings.hpp"
#include "process/IpfsProcessInitializer.hpp"


namespace Xeth{


class IpfsReader
{
    public:
        IpfsReader(const Settings &);

        QByteArray readBytes(const QString &);
        QJsonObject readJson(const QString &);

    private:
        const Settings &_settings;
};


}
