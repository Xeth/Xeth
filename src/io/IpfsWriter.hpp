#pragma once 

#include <QString>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QProcess>
#include <QByteArray>

#include "env/Settings.hpp"
#include "process/IpfsProcessInitializer.hpp"


namespace Xeth{


class IpfsWriter
{
    public:
        IpfsWriter(const Settings &);

        QString writeFile(const QString &path);
        QString writeData(const QString &);
        QString writeData(const QJsonObject &);
        QString writeData(const QVariantMap &);
        QString writeData(const QByteArray &);

    private:
        QString execute(QProcess &);

    private:
        const Settings &_settings;
};


}

