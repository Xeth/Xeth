#pragma once

#include <QProcess>
#include <QString>
#include <QStringList>

#include "env/Settings.hpp"


namespace Xeth{


class IpfsProcessInitializer
{
    public:
        static void Initialize(QProcess &);
        static void Initialize(QProcess &, const Settings &);
        static void Initialize(QProcess &, const Settings &, const QStringList &args);

        static void InitializeDaemon(QProcess &);
        static void InitializeDaemon(QProcess &, const Settings &);
        static void InitializeDaemon(QProcess &, const Settings &, const QStringList &args);

        static QString GetCommand(const Settings &);
        static QStringList GetDaemonArguments();
};


}
