#pragma once

#include <QProcess>
#include <QString>
#include <QStringList>
#include <QApplication>
#include <QFileInfo>

#include "conf/Settings.hpp"


namespace Xeth{


class EthProcessInitializer
{
    public:
        static void Initialize(QProcess &);
        static void Initialize(QProcess &, const Settings &);
        static void Initialize(QProcess &, const Settings &, const QStringList &args);

        static QString GetCommand(const Settings &);
        static QString GetDefaultCommand();
        static QStringList GetArguments(const Settings &);
};


}
