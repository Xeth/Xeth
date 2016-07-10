#pragma once 

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread.hpp>

#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QProcess>

#include "conf/Settings.hpp"
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
