#pragma once


#include <QString>
#include <QStringList>
#include <QProcess>


#include "conf/Settings.hpp"
#include "process/IpfsProcessInitializer.hpp"


namespace Xeth{


class IpfsNameRegistrar
{
    public:
        IpfsNameRegistrar(const Settings &);

        QString publish(const QString &);
        QString resolve(const QString &);

    private:
        QString execute(QProcess &);


    private:
        const Settings &_settings;
};



}
